/*
 * Copyright (c) 2021, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/TypeCasts.h>
#include <LibJS/Runtime/GlobalObject.h>
#include <LibJS/Runtime/Temporal/AbstractOperations.h>
#include <LibJS/Runtime/Temporal/Calendar.h>
#include <LibJS/Runtime/Temporal/PlainYearMonth.h>
#include <LibJS/Runtime/Temporal/PlainYearMonthPrototype.h>

namespace JS::Temporal {

// 9.3 Properties of the Temporal.PlainYearMonth Prototype Object, https://tc39.es/proposal-temporal/#sec-properties-of-the-temporal-plainyearmonth-prototype-object
PlainYearMonthPrototype::PlainYearMonthPrototype(GlobalObject& global_object)
    : PrototypeObject(*global_object.object_prototype())
{
}

void PlainYearMonthPrototype::initialize(GlobalObject& global_object)
{
    Object::initialize(global_object);

    auto& vm = this->vm();

    // 9.3.2 Temporal.PlainYearMonth.prototype[ @@toStringTag ], https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype-@@tostringtag
    define_direct_property(*vm.well_known_symbol_to_string_tag(), js_string(vm, "Temporal.PlainYearMonth"), Attribute::Configurable);

    define_native_accessor(vm.names.calendar, calendar_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.year, year_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.month, month_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.monthCode, month_code_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.daysInYear, days_in_year_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.daysInMonth, days_in_month_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.monthsInYear, months_in_year_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.inLeapYear, in_leap_year_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.era, era_getter, {}, Attribute::Configurable);
    define_native_accessor(vm.names.eraYear, era_year_getter, {}, Attribute::Configurable);

    u8 attr = Attribute::Writable | Attribute::Configurable;
    define_native_function(vm.names.equals, equals, 1, attr);
    define_native_function(vm.names.toString, to_string, 0, attr);
    define_native_function(vm.names.toLocaleString, to_locale_string, 0, attr);
    define_native_function(vm.names.toJSON, to_json, 0, attr);
    define_native_function(vm.names.valueOf, value_of, 0, attr);
    define_native_function(vm.names.toPlainDate, to_plain_date, 1, attr);
    define_native_function(vm.names.getISOFields, get_iso_fields, 0, attr);
}

// 9.3.3 get Temporal.PlainYearMonth.prototype.calendar, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.calendar
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::calendar_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Return yearMonth.[[Calendar]].
    return Value(&year_month->calendar());
}

// 9.3.4 get Temporal.PlainYearMonth.prototype.year, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.year
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::year_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return 𝔽(? CalendarYear(calendar, yearMonth)).
    return Value(TRY_OR_DISCARD(calendar_year(global_object, calendar, *year_month)));
}

// 9.3.5 get Temporal.PlainYearMonth.prototype.month, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.month
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::month_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return 𝔽(? CalendarMonth(calendar, yearMonth)).
    return Value(TRY_OR_DISCARD(calendar_month(global_object, calendar, *year_month)));
}

// 9.3.6 get Temporal.PlainYearMonth.prototype.monthCode, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.monthCode
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::month_code_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return ? CalendarMonthCode(calendar, yearMonth).
    return js_string(vm, TRY_OR_DISCARD(calendar_month_code(global_object, calendar, *year_month)));
}

// 9.3.7 get Temporal.PlainYearMonth.prototype.daysInYear, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.daysinyear
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::days_in_year_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return ? CalendarDaysInYear(calendar, yearMonth).
    return Value(TRY_OR_DISCARD(calendar_days_in_year(global_object, calendar, *year_month)));
}

// 9.3.8 get Temporal.PlainYearMonth.prototype.daysInMonth, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.daysinmonth
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::days_in_month_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return ? CalendarDaysInMonth(calendar, yearMonth).
    return Value(TRY_OR_DISCARD(calendar_days_in_month(global_object, calendar, *year_month)));
}

// 9.3.9 get Temporal.PlainYearMonth.prototype.monthsInYear, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.monthsinyear
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::months_in_year_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return ? CalendarMonthsInYear(calendar, yearMonth).
    return Value(TRY_OR_DISCARD(calendar_months_in_year(global_object, calendar, *year_month)));
}

// 9.3.10 get Temporal.PlainYearMonth.prototype.inLeapYear, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.inleapyear
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::in_leap_year_getter)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 4. Return ? CalendarInLeapYear(calendar, yearMonth).
    return Value(TRY_OR_DISCARD(calendar_in_leap_year(global_object, calendar, *year_month)));
}

// 15.6.9.2 get Temporal.PlainYearMonth.prototype.era, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.era
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::era_getter)
{
    // 1. Let plainYearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(plainYearMonth, [[InitializedTemporalYearMonth]]).
    auto* plain_year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be plainYearMonth.[[Calendar]].
    auto& calendar = plain_year_month->calendar();

    // 4. Return ? CalendarEra(calendar, plainYearMonth).
    return TRY_OR_DISCARD(calendar_era(global_object, calendar, *plain_year_month));
}

// 15.6.9.3 get Temporal.PlainYearMonth.prototype.eraYear, https://tc39.es/proposal-temporal/#sec-get-temporal.plainyearmonth.prototype.erayear
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::era_year_getter)
{
    // 1. Let plainYearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(plainYearMonth, [[InitializedTemporalYearMonth]]).
    auto* plain_year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let calendar be plainYearMonth.[[Calendar]].
    auto& calendar = plain_year_month->calendar();

    // 4. Return ? CalendarEraYear(calendar, plainYearMonth).
    return TRY_OR_DISCARD(calendar_era_year(global_object, calendar, *plain_year_month));
}

// 9.3.16 Temporal.PlainYearMonth.prototype.equals ( other ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.equals
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::equals)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Set other to ? ToTemporalYearMonth(other).
    auto* other = TRY_OR_DISCARD(to_temporal_year_month(global_object, vm.argument(0)));

    // 4. If yearMonth.[[ISOYear]] ≠ other.[[ISOYear]], return false.
    if (year_month->iso_year() != other->iso_year())
        return Value(false);

    // 5. If yearMonth.[[ISOMonth]] ≠ other.[[ISOMonth]], return false.
    if (year_month->iso_month() != other->iso_month())
        return Value(false);

    // 6. If yearMonth.[[ISODay]] ≠ other.[[ISODay]], return false.
    if (year_month->iso_day() != other->iso_day())
        return Value(false);

    // 7. Return ? CalendarEquals(yearMonth.[[Calendar]], other.[[Calendar]]).
    return Value(TRY_OR_DISCARD(calendar_equals(global_object, year_month->calendar(), other->calendar())));
}

// 9.3.17 Temporal.PlainYearMonth.prototype.toString ( [ options ] ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.tostring
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::to_string)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Set options to ? GetOptionsObject(options).
    auto* options = TRY_OR_DISCARD(get_options_object(global_object, vm.argument(0)));

    // 4. Let showCalendar be ? ToShowCalendarOption(options).
    auto show_calendar = TRY_OR_DISCARD(to_show_calendar_option(global_object, *options));

    // 5. Return ? TemporalYearMonthToString(yearMonth, showCalendar).
    return js_string(vm, TRY_OR_DISCARD(temporal_year_month_to_string(global_object, *year_month, show_calendar)));
}

// 9.3.18 Temporal.PlainYearMonth.prototype.toLocaleString ( [ locales [ , options ] ] ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.tolocalestring
// NOTE: This is the minimum toLocaleString implementation for engines without ECMA-402.
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::to_locale_string)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Return ? TemporalYearMonthToString(yearMonth, "auto").
    return js_string(vm, TRY_OR_DISCARD(temporal_year_month_to_string(global_object, *year_month, "auto"sv)));
}

// 9.3.19 Temporal.PlainYearMonth.prototype.toJSON ( ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.tojson
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::to_json)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Return ? TemporalYearMonthToString(yearMonth, "auto").
    return js_string(vm, TRY_OR_DISCARD(temporal_year_month_to_string(global_object, *year_month, "auto"sv)));
}

// 9.3.20 Temporal.PlainYearMonth.prototype.valueOf ( ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.valueof
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::value_of)
{
    // 1. Throw a TypeError exception.
    vm.throw_exception<TypeError>(global_object, ErrorType::Convert, "Temporal.PlainYearMonth", "a primitive value");
    return {};
}

// 9.3.21 Temporal.PlainYearMonth.prototype.toPlainDate ( item ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.toplaindate
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::to_plain_date)
{
    auto item = vm.argument(0);

    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. If Type(item) is not Object, then
    if (!item.is_object()) {
        // a. Throw a TypeError exception.
        vm.throw_exception<TypeError>(global_object, ErrorType::NotAnObject, item);
        return {};
    }

    // 4. Let calendar be yearMonth.[[Calendar]].
    auto& calendar = year_month->calendar();

    // 5. Let receiverFieldNames be ? CalendarFields(calendar, « "monthCode", "year" »).
    auto receiver_field_names = TRY_OR_DISCARD(calendar_fields(global_object, calendar, { "monthCode"sv, "year"sv }));

    // 6. Let fields be ? PrepareTemporalFields(yearMonth, receiverFieldNames, «»).
    auto* fields = TRY_OR_DISCARD(prepare_temporal_fields(global_object, *year_month, receiver_field_names, {}));

    // 7. Let inputFieldNames be ? CalendarFields(calendar, « "day" »).
    auto input_field_names = TRY_OR_DISCARD(calendar_fields(global_object, calendar, { "day"sv }));

    // 8. Let inputFields be ? PrepareTemporalFields(item, inputFieldNames, «»).
    auto* input_fields = TRY_OR_DISCARD(prepare_temporal_fields(global_object, item.as_object(), input_field_names, {}));

    // 9. Let mergedFields be ? CalendarMergeFields(calendar, fields, inputFields).
    auto* merged_fields = TRY_OR_DISCARD(calendar_merge_fields(global_object, calendar, *fields, *input_fields));

    // 10. Let mergedFieldNames be the List containing all the elements of receiverFieldNames followed by all the elements of inputFieldNames, with duplicate elements removed.
    Vector<String> merged_field_names;
    for (auto& field_name : receiver_field_names) {
        if (!merged_field_names.contains_slow(field_name))
            merged_field_names.append(move(field_name));
    }
    for (auto& field_name : input_field_names) {
        if (!merged_field_names.contains_slow(field_name))
            merged_field_names.append(move(field_name));
    }

    // 11. Set mergedFields to ? PrepareTemporalFields(mergedFields, mergedFieldNames, «»).
    merged_fields = TRY_OR_DISCARD(prepare_temporal_fields(global_object, *merged_fields, merged_field_names, {}));

    // 12. Let options be ! OrdinaryObjectCreate(null).
    auto* options = Object::create(global_object, nullptr);

    // 13. Perform ! CreateDataPropertyOrThrow(options, "overflow", "reject").
    MUST(options->create_data_property_or_throw(vm.names.overflow, js_string(vm, vm.names.reject.as_string())));

    // 14. Return ? DateFromFields(calendar, mergedFields, options).
    return TRY_OR_DISCARD(date_from_fields(global_object, calendar, *merged_fields, *options));
}

// 9.3.22 Temporal.PlainYearMonth.prototype.getISOFields ( ), https://tc39.es/proposal-temporal/#sec-temporal.plainyearmonth.prototype.getisofields
JS_DEFINE_NATIVE_FUNCTION(PlainYearMonthPrototype::get_iso_fields)
{
    // 1. Let yearMonth be the this value.
    // 2. Perform ? RequireInternalSlot(yearMonth, [[InitializedTemporalYearMonth]]).
    auto* year_month = TRY_OR_DISCARD(typed_this_object(global_object));

    // 3. Let fields be ! OrdinaryObjectCreate(%Object.prototype%).
    auto* fields = Object::create(global_object, global_object.object_prototype());

    // 4. Perform ! CreateDataPropertyOrThrow(fields, "calendar", yearMonth.[[Calendar]]).
    MUST(fields->create_data_property_or_throw(vm.names.calendar, Value(&year_month->calendar())));

    // 5. Perform ! CreateDataPropertyOrThrow(fields, "isoDay", 𝔽(yearMonth.[[ISODay]])).
    MUST(fields->create_data_property_or_throw(vm.names.isoDay, Value(year_month->iso_day())));

    // 6. Perform ! CreateDataPropertyOrThrow(fields, "isoMonth", 𝔽(yearMonth.[[ISOMonth]])).
    MUST(fields->create_data_property_or_throw(vm.names.isoMonth, Value(year_month->iso_month())));

    // 7. Perform ! CreateDataPropertyOrThrow(fields, "isoYear", 𝔽(yearMonth.[[ISOYear]])).
    MUST(fields->create_data_property_or_throw(vm.names.isoYear, Value(year_month->iso_year())));

    // 8. Return fields.
    return fields;
}

}
