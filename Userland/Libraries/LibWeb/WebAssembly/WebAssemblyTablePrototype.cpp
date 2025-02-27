/*
 * Copyright (c) 2021, Ali Mohammad Pur <mpfard@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Runtime/TypedArray.h>
#include <LibWeb/WebAssembly/WebAssemblyTableObject.h>
#include <LibWeb/WebAssembly/WebAssemblyTablePrototype.h>

namespace Web::Bindings {

void WebAssemblyTablePrototype::initialize(JS::GlobalObject& global_object)
{
    Object::initialize(global_object);
    define_native_accessor("length", length_getter, {}, JS::Attribute::Enumerable | JS::Attribute::Configurable);
    define_native_function("grow", grow, 1, JS::Attribute::Writable | JS::Attribute::Enumerable | JS::Attribute::Configurable);
    define_native_function("get", get, 1, JS::Attribute::Writable | JS::Attribute::Enumerable | JS::Attribute::Configurable);
    define_native_function("set", set, 1, JS::Attribute::Writable | JS::Attribute::Enumerable | JS::Attribute::Configurable);
}

JS_DEFINE_NATIVE_FUNCTION(WebAssemblyTablePrototype::grow)
{
    auto delta = TRY_OR_DISCARD(vm.argument(0).to_u32(global_object));

    auto* this_object = TRY_OR_DISCARD(vm.this_value(global_object).to_object(global_object));
    if (!is<WebAssemblyTableObject>(this_object)) {
        vm.throw_exception<JS::TypeError>(global_object, JS::ErrorType::NotAnObjectOfType, "WebAssembly.Table");
        return {};
    }
    auto* table_object = static_cast<WebAssemblyTableObject*>(this_object);
    auto address = table_object->address();
    auto* table = WebAssemblyObject::s_abstract_machine.store().get(address);
    if (!table)
        return JS::js_undefined();

    auto initial_size = table->elements().size();
    auto value_value = vm.argument(1);
    auto reference_value = [&]() -> Optional<Wasm::Value> {
        if (value_value.is_undefined())
            return Wasm::Value(table->type().element_type(), 0ull);

        return to_webassembly_value(value_value, table->type().element_type(), global_object);
    }();

    if (!reference_value.has_value())
        return {};

    auto& reference = reference_value->value().get<Wasm::Reference>();

    if (!table->grow(delta, reference)) {
        vm.throw_exception<JS::RangeError>(global_object, "Failed to grow table");
        return {};
    }

    return JS::Value(static_cast<u32>(initial_size));
}

JS_DEFINE_NATIVE_FUNCTION(WebAssemblyTablePrototype::get)
{
    auto index = TRY_OR_DISCARD(vm.argument(0).to_u32(global_object));

    auto* this_object = TRY_OR_DISCARD(vm.this_value(global_object).to_object(global_object));
    if (!is<WebAssemblyTableObject>(this_object)) {
        vm.throw_exception<JS::TypeError>(global_object, JS::ErrorType::NotAnObjectOfType, "WebAssembly.Table");
        return {};
    }
    auto* table_object = static_cast<WebAssemblyTableObject*>(this_object);
    auto address = table_object->address();
    auto* table = WebAssemblyObject::s_abstract_machine.store().get(address);
    if (!table)
        return JS::js_undefined();

    if (table->elements().size() <= index) {
        vm.throw_exception<JS::RangeError>(global_object, "Table element index out of range");
        return {};
    }

    auto& ref = table->elements()[index];
    if (!ref.has_value())
        return JS::js_undefined();

    Wasm::Value wasm_value { ref.value() };
    return to_js_value(wasm_value, global_object);
}

JS_DEFINE_NATIVE_FUNCTION(WebAssemblyTablePrototype::set)
{
    auto index = TRY_OR_DISCARD(vm.argument(0).to_u32(global_object));

    auto* this_object = TRY_OR_DISCARD(vm.this_value(global_object).to_object(global_object));
    if (!is<WebAssemblyTableObject>(this_object)) {
        vm.throw_exception<JS::TypeError>(global_object, JS::ErrorType::NotAnObjectOfType, "WebAssembly.Table");
        return {};
    }
    auto* table_object = static_cast<WebAssemblyTableObject*>(this_object);
    auto address = table_object->address();
    auto* table = WebAssemblyObject::s_abstract_machine.store().get(address);
    if (!table)
        return JS::js_undefined();

    if (table->elements().size() <= index) {
        vm.throw_exception<JS::RangeError>(global_object, "Table element index out of range");
        return {};
    }

    auto value_value = vm.argument(1);
    auto reference_value = [&]() -> Optional<Wasm::Value> {
        if (value_value.is_undefined())
            return Wasm::Value(table->type().element_type(), 0ull);

        return to_webassembly_value(value_value, table->type().element_type(), global_object);
    }();

    if (!reference_value.has_value())
        return {};

    auto& reference = reference_value->value().get<Wasm::Reference>();
    table->elements()[index] = reference;

    return JS::js_undefined();
}

JS_DEFINE_NATIVE_FUNCTION(WebAssemblyTablePrototype::length_getter)
{
    auto* this_object = TRY_OR_DISCARD(vm.this_value(global_object).to_object(global_object));
    if (!is<WebAssemblyTableObject>(this_object)) {
        vm.throw_exception<JS::TypeError>(global_object, JS::ErrorType::NotAnObjectOfType, "WebAssembly.Table");
        return {};
    }
    auto* table_object = static_cast<WebAssemblyTableObject*>(this_object);
    auto address = table_object->address();
    auto* table = WebAssemblyObject::s_abstract_machine.store().get(address);
    if (!table)
        return JS::js_undefined();

    return JS::Value(table->elements().size());
}

}
