/*
 * Copyright (c) 2021, Sahan Fernando <sahan.h.fernando@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Kernel/Bus/PCI/API.h>
#include <Kernel/Bus/PCI/IDs.h>
#include <Kernel/Graphics/Console/GenericFramebufferConsole.h>
#include <Kernel/Graphics/GraphicsManagement.h>
#include <Kernel/Graphics/VirtIOGPU/GPU.h>
#include <Kernel/Graphics/VirtIOGPU/GraphicsAdapter.h>

namespace Kernel::Graphics::VirtIOGPU {

NonnullRefPtr<GraphicsAdapter> GraphicsAdapter::initialize(PCI::DeviceIdentifier const& device_identifier)
{
    VERIFY(device_identifier.hardware_id().vendor_id == PCI::VendorID::VirtIO);
    return adopt_ref(*new GraphicsAdapter(device_identifier));
}

GraphicsAdapter::GraphicsAdapter(PCI::DeviceIdentifier const& device_identifier)
    : PCI::Device(device_identifier.address())
{
    m_gpu_device = adopt_ref(*new GPU(device_identifier)).leak_ref();
    m_gpu_device->initialize();
}

void GraphicsAdapter::initialize_framebuffer_devices()
{
    dbgln_if(VIRTIO_DEBUG, "GPU: Initializing framebuffer devices");
    VERIFY(!m_created_framebuffer_devices);
    m_gpu_device->create_framebuffer_devices();
    m_created_framebuffer_devices = true;

    // FIXME: This is a very wrong way to do this...
    GraphicsManagement::the().m_console = m_gpu_device->default_console();
}

void GraphicsAdapter::enable_consoles()
{
    dbgln_if(VIRTIO_DEBUG, "GPU: Enabling consoles");
    m_gpu_device->for_each_framebuffer([&](auto& framebuffer, auto& console) {
        framebuffer.deactivate_writes();
        console.enable();
        return IterationDecision::Continue;
    });
}

void GraphicsAdapter::disable_consoles()
{
    dbgln_if(VIRTIO_DEBUG, "GPU: Disabling consoles");
    m_gpu_device->for_each_framebuffer([&](auto& framebuffer, auto& console) {
        console.disable();
        framebuffer.activate_writes();
        return IterationDecision::Continue;
    });
}

}
