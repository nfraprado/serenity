/*
 * Copyright (c) 2021, Matthew Olsson <mattco@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Bytecode/Interpreter.h>
#include <LibJS/Runtime/GeneratorObjectPrototype.h>
#include <LibJS/Runtime/GlobalObject.h>

namespace JS {

GeneratorObjectPrototype::GeneratorObjectPrototype(GlobalObject& global_object)
    : PrototypeObject(*global_object.iterator_prototype())
{
}

void GeneratorObjectPrototype::initialize(GlobalObject& global_object)
{
    auto& vm = this->vm();
    Object::initialize(global_object);
    u8 attr = Attribute::Writable | Attribute::Configurable;
    define_native_function(vm.names.next, next, 1, attr);
    define_native_function(vm.names.return_, return_, 1, attr);
    define_native_function(vm.names.throw_, throw_, 1, attr);

    // 27.5.1.5 Generator.prototype [ @@toStringTag ], https://tc39.es/ecma262/#sec-generator.prototype-@@tostringtag
    define_direct_property(*vm.well_known_symbol_to_string_tag(), js_string(vm, "Generator"), Attribute::Configurable);
}

GeneratorObjectPrototype::~GeneratorObjectPrototype()
{
}

// 27.5.1.2 Generator.prototype.next ( value ), https://tc39.es/ecma262/#sec-generator.prototype.next
JS_DEFINE_NATIVE_FUNCTION(GeneratorObjectPrototype::next)
{
    auto* generator_object = TRY_OR_DISCARD(typed_this_object(global_object));
    return generator_object->next_impl(vm, global_object, {});
}

// 27.5.1.3 Generator.prototype.next ( value ), https://tc39.es/ecma262/#sec-generator.prototype.return
JS_DEFINE_NATIVE_FUNCTION(GeneratorObjectPrototype::return_)
{
    auto* generator_object = TRY_OR_DISCARD(typed_this_object(global_object));
    generator_object->set_done();
    return generator_object->next_impl(vm, global_object, {});
}

// 27.5.1.4 Generator.prototype.next ( value ), https://tc39.es/ecma262/#sec-generator.prototype.throw
JS_DEFINE_NATIVE_FUNCTION(GeneratorObjectPrototype::throw_)
{
    auto* generator_object = TRY_OR_DISCARD(typed_this_object(global_object));
    return generator_object->next_impl(vm, global_object, vm.argument(0));
}

}
