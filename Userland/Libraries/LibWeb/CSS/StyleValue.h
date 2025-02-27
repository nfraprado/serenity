/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Tobias Christiansen <tobyase@serenityos.org>
 * Copyright (c) 2021, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Function.h>
#include <AK/NonnullOwnPtr.h>
#include <AK/NonnullOwnPtrVector.h>
#include <AK/NonnullRefPtrVector.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <AK/URL.h>
#include <AK/Variant.h>
#include <AK/Vector.h>
#include <AK/WeakPtr.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Color.h>
#include <LibWeb/CSS/Display.h>
#include <LibWeb/CSS/Length.h>
#include <LibWeb/CSS/PropertyID.h>
#include <LibWeb/CSS/ValueID.h>
#include <LibWeb/Forward.h>
#include <LibWeb/Loader/ImageResource.h>

namespace Web::CSS {

enum class AlignItems {
    FlexStart,
    FlexEnd,
    Center,
    Baseline,
    Stretch,
};

enum class BoxSizing {
    BorderBox,
    ContentBox,
};

enum class Clear {
    None,
    Left,
    Right,
    Both,
};

enum class Cursor {
    Auto,
    Default,
    None,
    ContextMenu,
    Help,
    Pointer,
    Progress,
    Wait,
    Cell,
    Crosshair,
    Text,
    VerticalText,
    Alias,
    Copy,
    Move,
    NoDrop,
    NotAllowed,
    Grab,
    Grabbing,
    EResize,
    NResize,
    NeResize,
    NwResize,
    SResize,
    SeResize,
    SwResize,
    WResize,
    EwResize,
    NsResize,
    NeswResize,
    NwseResize,
    ColResize,
    RowResize,
    AllScroll,
    ZoomIn,
    ZoomOut,
};

enum class FlexBasis {
    Content,
    Length,
    Auto,
};

enum class FlexDirection {
    Row,
    RowReverse,
    Column,
    ColumnReverse,
};

enum class FlexWrap {
    Nowrap,
    Wrap,
    WrapReverse
};

enum class Float {
    None,
    Left,
    Right,
};

enum class JustifyContent {
    FlexStart,
    FlexEnd,
    Center,
    SpaceBetween,
    SpaceAround,
};

enum class LineStyle {
    None,
    Hidden,
    Dotted,
    Dashed,
    Solid,
    Double,
    Groove,
    Ridge,
    Inset,
    Outset,
};

enum class ListStyleType {
    None,
    Disc,
    Circle,
    Square,
    Decimal,
    DecimalLeadingZero,
    LowerAlpha,
    LowerLatin,
    LowerRoman,
    UpperAlpha,
    UpperLatin,
    UpperRoman,
};

enum class Overflow : u8 {
    Auto,
    Clip,
    Hidden,
    Scroll,
    Visible,
};

enum class Position {
    Static,
    Relative,
    Absolute,
    Fixed,
    Sticky,
};

enum class Repeat : u8 {
    NoRepeat,
    Repeat,
    Round,
    Space,
};

enum class TextAlign {
    Left,
    Center,
    Right,
    Justify,
    LibwebCenter,
};

enum class TextDecorationLine {
    None,
    Underline,
    Overline,
    LineThrough,
    Blink,
};

enum class TextTransform {
    None,
    Capitalize,
    Uppercase,
    Lowercase,
    FullWidth,
    FullSizeKana,
};

enum class TransformFunction {
    TranslateY,
};

enum class WhiteSpace {
    Normal,
    Pre,
    Nowrap,
    PreLine,
    PreWrap,
};

enum class PointerEvents {
    Auto,
    None
};

class StyleValue : public RefCounted<StyleValue> {
public:
    virtual ~StyleValue();

    enum class Type {
        Background,
        BackgroundRepeat,
        Border,
        BorderRadius,
        BoxShadow,
        Calculated,
        Color,
        CombinedBorderRadius,
        CustomProperty,
        Flex,
        FlexFlow,
        Font,
        Identifier,
        Image,
        Inherit,
        Initial,
        Invalid,
        Length,
        ListStyle,
        Numeric,
        Overflow,
        String,
        TextDecoration,
        Transformation,
        Unset,
        ValueList,
    };

    Type type() const { return m_type; }

    bool is_background() const { return type() == Type::Background; }
    bool is_background_repeat() const { return type() == Type::BackgroundRepeat; }
    bool is_border() const { return type() == Type::Border; }
    bool is_border_radius() const { return type() == Type::BorderRadius; }
    bool is_box_shadow() const { return type() == Type::BoxShadow; }
    bool is_calculated() const { return type() == Type::Calculated; }
    bool is_color() const { return type() == Type::Color; }
    bool is_custom_property() const { return type() == Type::CustomProperty; }
    bool is_flex() const { return type() == Type::Flex; }
    bool is_flex_flow() const { return type() == Type::FlexFlow; }
    bool is_font() const { return type() == Type::Font; }
    bool is_identifier() const { return type() == Type::Identifier; }
    bool is_image() const { return type() == Type::Image; }
    bool is_inherit() const { return type() == Type::Inherit; }
    bool is_initial() const { return type() == Type::Initial; }
    bool is_length() const { return type() == Type::Length; }
    bool is_list_style() const { return type() == Type::ListStyle; }
    bool is_numeric() const { return type() == Type::Numeric; }
    bool is_overflow() const { return type() == Type::Overflow; }
    bool is_string() const { return type() == Type::String; }
    bool is_text_decoration() const { return type() == Type::TextDecoration; }
    bool is_transformation() const { return type() == Type::Transformation; }
    bool is_unset() const { return type() == Type::Unset; }
    bool is_value_list() const { return type() == Type::ValueList; }

    bool is_builtin() const { return is_inherit() || is_initial() || is_unset(); }

    BackgroundRepeatStyleValue const& as_background_repeat() const;
    BackgroundStyleValue const& as_background() const;
    BorderRadiusStyleValue const& as_border_radius() const;
    BorderStyleValue const& as_border() const;
    BoxShadowStyleValue const& as_box_shadow() const;
    CalculatedStyleValue const& as_calculated() const;
    ColorStyleValue const& as_color() const;
    CustomStyleValue const& as_custom_property() const;
    FlexFlowStyleValue const& as_flex_flow() const;
    FlexStyleValue const& as_flex() const;
    FontStyleValue const& as_font() const;
    IdentifierStyleValue const& as_identifier() const;
    ImageStyleValue const& as_image() const;
    InheritStyleValue const& as_inherit() const;
    InitialStyleValue const& as_initial() const;
    LengthStyleValue const& as_length() const;
    ListStyleStyleValue const& as_list_style() const;
    NumericStyleValue const& as_numeric() const;
    OverflowStyleValue const& as_overflow() const;
    StringStyleValue const& as_string() const;
    TextDecorationStyleValue const& as_text_decoration() const;
    TransformationStyleValue const& as_transformation() const;
    UnsetStyleValue const& as_unset() const;
    StyleValueList const& as_value_list() const;

    BackgroundRepeatStyleValue& as_background_repeat() { return const_cast<BackgroundRepeatStyleValue&>(const_cast<StyleValue const&>(*this).as_background_repeat()); }
    BackgroundStyleValue& as_background() { return const_cast<BackgroundStyleValue&>(const_cast<StyleValue const&>(*this).as_background()); }
    BorderRadiusStyleValue& as_border_radius() { return const_cast<BorderRadiusStyleValue&>(const_cast<StyleValue const&>(*this).as_border_radius()); }
    BorderStyleValue& as_border() { return const_cast<BorderStyleValue&>(const_cast<StyleValue const&>(*this).as_border()); }
    BoxShadowStyleValue& as_box_shadow() { return const_cast<BoxShadowStyleValue&>(const_cast<StyleValue const&>(*this).as_box_shadow()); }
    CalculatedStyleValue& as_calculated() { return const_cast<CalculatedStyleValue&>(const_cast<StyleValue const&>(*this).as_calculated()); }
    ColorStyleValue& as_color() { return const_cast<ColorStyleValue&>(const_cast<StyleValue const&>(*this).as_color()); }
    CustomStyleValue& as_custom_property() { return const_cast<CustomStyleValue&>(const_cast<StyleValue const&>(*this).as_custom_property()); }
    FlexFlowStyleValue& as_flex_flow() { return const_cast<FlexFlowStyleValue&>(const_cast<StyleValue const&>(*this).as_flex_flow()); }
    FlexStyleValue& as_flex() { return const_cast<FlexStyleValue&>(const_cast<StyleValue const&>(*this).as_flex()); }
    FontStyleValue& as_font() { return const_cast<FontStyleValue&>(const_cast<StyleValue const&>(*this).as_font()); }
    IdentifierStyleValue& as_identifier() { return const_cast<IdentifierStyleValue&>(const_cast<StyleValue const&>(*this).as_identifier()); }
    ImageStyleValue& as_image() { return const_cast<ImageStyleValue&>(const_cast<StyleValue const&>(*this).as_image()); }
    InheritStyleValue& as_inherit() { return const_cast<InheritStyleValue&>(const_cast<StyleValue const&>(*this).as_inherit()); }
    InitialStyleValue& as_initial() { return const_cast<InitialStyleValue&>(const_cast<StyleValue const&>(*this).as_initial()); }
    LengthStyleValue& as_length() { return const_cast<LengthStyleValue&>(const_cast<StyleValue const&>(*this).as_length()); }
    ListStyleStyleValue& as_list_style() { return const_cast<ListStyleStyleValue&>(const_cast<StyleValue const&>(*this).as_list_style()); }
    NumericStyleValue& as_numeric() { return const_cast<NumericStyleValue&>(const_cast<StyleValue const&>(*this).as_numeric()); }
    OverflowStyleValue& as_overflow() { return const_cast<OverflowStyleValue&>(const_cast<StyleValue const&>(*this).as_overflow()); }
    StringStyleValue& as_string() { return const_cast<StringStyleValue&>(const_cast<StyleValue const&>(*this).as_string()); }
    TextDecorationStyleValue& as_text_decoration() { return const_cast<TextDecorationStyleValue&>(const_cast<StyleValue const&>(*this).as_text_decoration()); }
    TransformationStyleValue& as_transformation() { return const_cast<TransformationStyleValue&>(const_cast<StyleValue const&>(*this).as_transformation()); }
    UnsetStyleValue& as_unset() { return const_cast<UnsetStyleValue&>(const_cast<StyleValue const&>(*this).as_unset()); }
    StyleValueList& as_value_list() { return const_cast<StyleValueList&>(const_cast<StyleValue const&>(*this).as_value_list()); }

    virtual bool has_auto() const { return false; }
    virtual bool has_color() const { return false; }
    virtual bool has_identifier() const { return false; }
    virtual bool has_length() const { return false; }
    virtual bool has_number() const { return false; }

    virtual Color to_color(Layout::NodeWithStyle const&) const { return {}; }
    virtual CSS::ValueID to_identifier() const { return ValueID::Invalid; }
    virtual Length to_length() const { return {}; }
    virtual float to_number() const { return {}; }
    virtual String to_string() const = 0;

    bool operator==(StyleValue const& other) const { return equals(other); }
    bool operator!=(StyleValue const& other) const { return !(*this == other); }

    virtual bool equals(StyleValue const& other) const
    {
        if (type() != other.type())
            return false;
        return to_string() == other.to_string();
    }

    virtual void visit_lengths(Function<void(CSS::Length&)>) { }

protected:
    explicit StyleValue(Type);

private:
    Type m_type { Type::Invalid };
};

class BackgroundStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<BackgroundStyleValue> create(
        NonnullRefPtr<StyleValue> color,
        NonnullRefPtr<StyleValue> image,
        NonnullRefPtr<StyleValue> repeat_x,
        NonnullRefPtr<StyleValue> repeat_y)
    {
        return adopt_ref(*new BackgroundStyleValue(color, image, repeat_x, repeat_y));
    }
    virtual ~BackgroundStyleValue() override { }

    NonnullRefPtr<StyleValue> color() const { return m_color; }
    NonnullRefPtr<StyleValue> image() const { return m_image; }
    NonnullRefPtr<StyleValue> repeat_x() const { return m_repeat_x; }
    NonnullRefPtr<StyleValue> repeat_y() const { return m_repeat_y; }

    virtual String to_string() const override
    {
        return String::formatted("{} {} {} {}", m_color->to_string(), m_image->to_string(), m_repeat_x->to_string(), m_repeat_y->to_string());
    }

private:
    BackgroundStyleValue(
        NonnullRefPtr<StyleValue> color,
        NonnullRefPtr<StyleValue> image,
        NonnullRefPtr<StyleValue> repeat_x,
        NonnullRefPtr<StyleValue> repeat_y)
        : StyleValue(Type::Background)
        , m_color(color)
        , m_image(image)
        , m_repeat_x(repeat_x)
        , m_repeat_y(repeat_y)
    {
    }
    NonnullRefPtr<StyleValue> m_color;
    NonnullRefPtr<StyleValue> m_image;
    // FIXME: background-position
    // FIXME: background-size
    NonnullRefPtr<StyleValue> m_repeat_x;
    NonnullRefPtr<StyleValue> m_repeat_y;
    // FIXME: background-attachment
    // FIXME: background-clip
    // FIXME: background-origin
};

class BackgroundRepeatStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<BackgroundRepeatStyleValue> create(NonnullRefPtr<StyleValue> repeat_x, NonnullRefPtr<StyleValue> repeat_y)
    {
        return adopt_ref(*new BackgroundRepeatStyleValue(repeat_x, repeat_y));
    }
    virtual ~BackgroundRepeatStyleValue() override { }

    NonnullRefPtr<StyleValue> repeat_x() const { return m_repeat_x; }
    NonnullRefPtr<StyleValue> repeat_y() const { return m_repeat_y; }

    virtual String to_string() const override
    {
        return String::formatted("{} {}", m_repeat_x->to_string(), m_repeat_y->to_string());
    }

private:
    BackgroundRepeatStyleValue(NonnullRefPtr<StyleValue> repeat_x, NonnullRefPtr<StyleValue> repeat_y)
        : StyleValue(Type::BackgroundRepeat)
        , m_repeat_x(repeat_x)
        , m_repeat_y(repeat_y)
    {
    }

    NonnullRefPtr<StyleValue> m_repeat_x;
    NonnullRefPtr<StyleValue> m_repeat_y;
};

class BorderStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<BorderStyleValue> create(
        NonnullRefPtr<StyleValue> border_width,
        NonnullRefPtr<StyleValue> border_style,
        NonnullRefPtr<StyleValue> border_color)
    {
        return adopt_ref(*new BorderStyleValue(border_width, border_style, border_color));
    }
    virtual ~BorderStyleValue() override { }

    NonnullRefPtr<StyleValue> border_width() const { return m_border_width; }
    NonnullRefPtr<StyleValue> border_style() const { return m_border_style; }
    NonnullRefPtr<StyleValue> border_color() const { return m_border_color; }

    virtual String to_string() const override
    {
        return String::formatted("Border border_width: {}, border_style: {}, border_color: {}", m_border_width->to_string(), m_border_style->to_string(), m_border_color->to_string());
    }

private:
    BorderStyleValue(
        NonnullRefPtr<StyleValue> border_width,
        NonnullRefPtr<StyleValue> border_style,
        NonnullRefPtr<StyleValue> border_color)
        : StyleValue(Type::Border)
        , m_border_width(border_width)
        , m_border_style(border_style)
        , m_border_color(border_color)
    {
    }

    NonnullRefPtr<StyleValue> m_border_width;
    NonnullRefPtr<StyleValue> m_border_style;
    NonnullRefPtr<StyleValue> m_border_color;
};

class BorderRadiusStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<BorderRadiusStyleValue> create(Length const& horizontal_radius, Length const& vertical_radius)
    {
        return adopt_ref(*new BorderRadiusStyleValue(horizontal_radius, vertical_radius));
    }
    virtual ~BorderRadiusStyleValue() override { }

    Length const& horizontal_radius() const { return m_horizontal_radius; }
    Length const& vertical_radius() const { return m_vertical_radius; }
    bool is_elliptical() const { return m_is_elliptical; }

    // FIXME: Remove this once we support elliptical border-radius in Layout/Node.
    virtual Length to_length() const override { return horizontal_radius(); }

    virtual String to_string() const override
    {
        return String::formatted("{} / {}", m_horizontal_radius.to_string(), m_vertical_radius.to_string());
    }

    virtual bool equals(StyleValue const& other) const override
    {
        if (type() != other.type())
            return false;
        auto& other_value = static_cast<BorderRadiusStyleValue const&>(other);
        return m_is_elliptical == other_value.m_is_elliptical
            && m_horizontal_radius == other_value.m_horizontal_radius
            && m_vertical_radius == other_value.m_vertical_radius;
    }

private:
    BorderRadiusStyleValue(Length const& horizontal_radius, Length const& vertical_radius)
        : StyleValue(Type::BorderRadius)
        , m_horizontal_radius(horizontal_radius)
        , m_vertical_radius(vertical_radius)
    {
        m_is_elliptical = (m_horizontal_radius != m_vertical_radius);
    }

    virtual void visit_lengths(Function<void(CSS::Length&)> visitor) override
    {
        visitor(m_horizontal_radius);
        visitor(m_vertical_radius);
    }

    bool m_is_elliptical;
    Length m_horizontal_radius;
    Length m_vertical_radius;
};

class BoxShadowStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<BoxShadowStyleValue> create(Length const& offset_x, Length const& offset_y, Length const& blur_radius, Color const& color)
    {
        return adopt_ref(*new BoxShadowStyleValue(offset_x, offset_y, blur_radius, color));
    }
    virtual ~BoxShadowStyleValue() override { }

    Length const& offset_x() const { return m_offset_x; }
    Length const& offset_y() const { return m_offset_y; }
    Length const& blur_radius() const { return m_blur_radius; }
    Color const& color() const { return m_color; }

    String to_string() const override { return String::formatted("BoxShadow offset_x: {}, offset_y: {}, blur_radius: {}, color: {}",
        m_offset_x.to_string(), m_offset_y.to_string(), m_blur_radius.to_string(), m_color.to_string()); }

private:
    explicit BoxShadowStyleValue(Length const& offset_x, Length const& offset_y, Length const& blur_radius, Color const& color)
        : StyleValue(Type::BoxShadow)
        , m_offset_x(offset_x)
        , m_offset_y(offset_y)
        , m_blur_radius(blur_radius)
        , m_color(color)
    {
    }

    virtual void visit_lengths(Function<void(CSS::Length&)> visitor) override
    {
        visitor(m_offset_x);
        visitor(m_offset_y);
        visitor(m_blur_radius);
    }

    Length m_offset_x;
    Length m_offset_y;
    Length m_blur_radius;
    Color m_color;
};

class CalculatedStyleValue : public StyleValue {
public:
    struct CalcSum;
    struct CalcSumPartWithOperator;
    struct CalcProduct;
    struct CalcProductPartWithOperator;
    struct CalcNumberSum;
    struct CalcNumberSumPartWithOperator;
    struct CalcNumberProduct;
    struct CalcNumberProductPartWithOperator;

    using CalcNumberValue = Variant<float, NonnullOwnPtr<CalcNumberSum>>;
    using CalcValue = Variant<float, CSS::Length, NonnullOwnPtr<CalcSum>>;

    // This represents that: https://www.w3.org/TR/css-values-3/#calc-syntax
    struct CalcSum {
        CalcSum(NonnullOwnPtr<CalcProduct> first_calc_product, NonnullOwnPtrVector<CalcSumPartWithOperator> additional)
            : first_calc_product(move(first_calc_product))
            , zero_or_more_additional_calc_products(move(additional)) {};

        NonnullOwnPtr<CalcProduct> first_calc_product;
        NonnullOwnPtrVector<CalcSumPartWithOperator> zero_or_more_additional_calc_products;
    };

    struct CalcNumberSum {
        CalcNumberSum(NonnullOwnPtr<CalcNumberProduct> first_calc_number_product, NonnullOwnPtrVector<CalcNumberSumPartWithOperator> additional)
            : first_calc_number_product(move(first_calc_number_product))
            , zero_or_more_additional_calc_number_products(move(additional)) {};

        NonnullOwnPtr<CalcNumberProduct> first_calc_number_product;
        NonnullOwnPtrVector<CalcNumberSumPartWithOperator> zero_or_more_additional_calc_number_products;
    };

    struct CalcProduct {
        CalcValue first_calc_value;
        NonnullOwnPtrVector<CalcProductPartWithOperator> zero_or_more_additional_calc_values;
    };

    struct CalcSumPartWithOperator {
        enum Operation {
            Add,
            Subtract,
        };

        CalcSumPartWithOperator(Operation op, NonnullOwnPtr<CalcProduct> calc_product)
            : op(op)
            , calc_product(move(calc_product)) {};

        Operation op;
        NonnullOwnPtr<CalcProduct> calc_product;
    };

    struct CalcProductPartWithOperator {
        enum {
            Multiply,
            Divide,
        } op;
        Variant<CalcValue, CalcNumberValue> value;
    };

    struct CalcNumberProduct {
        CalcNumberValue first_calc_number_value;
        NonnullOwnPtrVector<CalcNumberProductPartWithOperator> zero_or_more_additional_calc_number_values;
    };

    struct CalcNumberProductPartWithOperator {
        enum {
            Multiply,
            Divide,
        } op;
        CalcNumberValue value;
    };

    struct CalcNumberSumPartWithOperator {
        enum Operation {
            Add,
            Subtract,
        };

        CalcNumberSumPartWithOperator(Operation op, NonnullOwnPtr<CalcNumberProduct> calc_number_product)
            : op(op)
            , calc_number_product(move(calc_number_product)) {};

        Operation op;
        NonnullOwnPtr<CalcNumberProduct> calc_number_product;
    };

    static NonnullRefPtr<CalculatedStyleValue> create(String const& expression_string, NonnullOwnPtr<CalcSum> calc_sum)
    {
        return adopt_ref(*new CalculatedStyleValue(expression_string, move(calc_sum)));
    }

    String to_string() const override { return m_expression_string; }
    NonnullOwnPtr<CalcSum> const& expression() const { return m_expression; }

private:
    explicit CalculatedStyleValue(String const& expression_string, NonnullOwnPtr<CalcSum> calc_sum)
        : StyleValue(Type::Calculated)
        , m_expression_string(expression_string)
        , m_expression(move(calc_sum))
    {
    }

    String m_expression_string;
    NonnullOwnPtr<CalcSum> m_expression;
};

class ColorStyleValue : public StyleValue {
public:
    static NonnullRefPtr<ColorStyleValue> create(Color color)
    {
        return adopt_ref(*new ColorStyleValue(color));
    }
    virtual ~ColorStyleValue() override { }

    Color color() const { return m_color; }
    virtual String to_string() const override;
    virtual bool has_color() const override { return true; }
    virtual Color to_color(Layout::NodeWithStyle const&) const override { return m_color; }

    virtual bool equals(StyleValue const& other) const override
    {
        if (type() != other.type())
            return false;
        return m_color == static_cast<const ColorStyleValue&>(other).m_color;
    }

private:
    explicit ColorStyleValue(Color color)
        : StyleValue(Type::Color)
        , m_color(color)
    {
    }

    Color m_color;
};

class CombinedBorderRadiusStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<CombinedBorderRadiusStyleValue> create(NonnullRefPtr<BorderRadiusStyleValue> top_left, NonnullRefPtr<BorderRadiusStyleValue> top_right, NonnullRefPtr<BorderRadiusStyleValue> bottom_right, NonnullRefPtr<BorderRadiusStyleValue> bottom_left)
    {
        return adopt_ref(*new CombinedBorderRadiusStyleValue(top_left, top_right, bottom_right, bottom_left));
    }
    virtual ~CombinedBorderRadiusStyleValue() override { }

    NonnullRefPtr<BorderRadiusStyleValue> top_left() const { return m_top_left; }
    NonnullRefPtr<BorderRadiusStyleValue> top_right() const { return m_top_right; }
    NonnullRefPtr<BorderRadiusStyleValue> bottom_right() const { return m_bottom_right; }
    NonnullRefPtr<BorderRadiusStyleValue> bottom_left() const { return m_bottom_left; }

    virtual String to_string() const override
    {
        return String::formatted("{} {} {} {} / {} {} {} {}", m_top_left->horizontal_radius().to_string(), m_top_right->horizontal_radius().to_string(), m_bottom_right->horizontal_radius().to_string(), m_bottom_left->horizontal_radius().to_string(), m_top_left->vertical_radius().to_string(), m_top_right->vertical_radius().to_string(), m_bottom_right->vertical_radius().to_string(), m_bottom_left->vertical_radius().to_string());
    }

private:
    CombinedBorderRadiusStyleValue(NonnullRefPtr<BorderRadiusStyleValue> top_left, NonnullRefPtr<BorderRadiusStyleValue> top_right, NonnullRefPtr<BorderRadiusStyleValue> bottom_right, NonnullRefPtr<BorderRadiusStyleValue> bottom_left)
        : StyleValue(Type::CombinedBorderRadius)
        , m_top_left(top_left)
        , m_top_right(top_right)
        , m_bottom_right(bottom_right)
        , m_bottom_left(bottom_left)
    {
    }

    NonnullRefPtr<BorderRadiusStyleValue> m_top_left;
    NonnullRefPtr<BorderRadiusStyleValue> m_top_right;
    NonnullRefPtr<BorderRadiusStyleValue> m_bottom_right;
    NonnullRefPtr<BorderRadiusStyleValue> m_bottom_left;
};

// FIXME: Allow for fallback
class CustomStyleValue : public StyleValue {
public:
    static NonnullRefPtr<CustomStyleValue> create(String const& custom_property_name)
    {
        return adopt_ref(*new CustomStyleValue(custom_property_name));
    }
    String custom_property_name() const { return m_custom_property_name; }
    String to_string() const override { return m_custom_property_name; }

private:
    explicit CustomStyleValue(String const& custom_property_name)
        : StyleValue(Type::CustomProperty)
        , m_custom_property_name(custom_property_name)
    {
    }

    String m_custom_property_name {};
};

class FlexStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<FlexStyleValue> create(
        NonnullRefPtr<StyleValue> grow,
        NonnullRefPtr<StyleValue> shrink,
        NonnullRefPtr<StyleValue> basis)
    {
        return adopt_ref(*new FlexStyleValue(grow, shrink, basis));
    }
    virtual ~FlexStyleValue() override { }

    NonnullRefPtr<StyleValue> grow() const { return m_grow; }
    NonnullRefPtr<StyleValue> shrink() const { return m_shrink; }
    NonnullRefPtr<StyleValue> basis() const { return m_basis; }

    virtual String to_string() const override
    {
        return String::formatted("Flex grow: {}, shrink: {}, basis: {}", m_grow->to_string(), m_shrink->to_string(), m_basis->to_string());
    }

private:
    FlexStyleValue(
        NonnullRefPtr<StyleValue> grow,
        NonnullRefPtr<StyleValue> shrink,
        NonnullRefPtr<StyleValue> basis)
        : StyleValue(Type::Flex)
        , m_grow(grow)
        , m_shrink(shrink)
        , m_basis(basis)
    {
    }

    NonnullRefPtr<StyleValue> m_grow;
    NonnullRefPtr<StyleValue> m_shrink;
    NonnullRefPtr<StyleValue> m_basis;
};

class FlexFlowStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<FlexFlowStyleValue> create(NonnullRefPtr<StyleValue> flex_direction, NonnullRefPtr<StyleValue> flex_wrap)
    {
        return adopt_ref(*new FlexFlowStyleValue(flex_direction, flex_wrap));
    }
    virtual ~FlexFlowStyleValue() override { }

    NonnullRefPtr<StyleValue> flex_direction() const { return m_flex_direction; }
    NonnullRefPtr<StyleValue> flex_wrap() const { return m_flex_wrap; }

    virtual String to_string() const override
    {
        return String::formatted("FlexFlow flex_direction: {}, flex_wrap: {}", m_flex_direction->to_string(), m_flex_wrap->to_string());
    }

private:
    FlexFlowStyleValue(NonnullRefPtr<StyleValue> flex_direction, NonnullRefPtr<StyleValue> flex_wrap)
        : StyleValue(Type::FlexFlow)
        , m_flex_direction(flex_direction)
        , m_flex_wrap(flex_wrap)
    {
    }

    NonnullRefPtr<StyleValue> m_flex_direction;
    NonnullRefPtr<StyleValue> m_flex_wrap;
};

class FontStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<FontStyleValue> create(NonnullRefPtr<StyleValue> font_style, NonnullRefPtr<StyleValue> font_weight, NonnullRefPtr<StyleValue> font_size, NonnullRefPtr<StyleValue> line_height, NonnullRefPtr<StyleValue> font_families) { return adopt_ref(*new FontStyleValue(font_style, font_weight, font_size, line_height, font_families)); }
    virtual ~FontStyleValue() override { }

    NonnullRefPtr<StyleValue> font_style() const { return m_font_style; }
    NonnullRefPtr<StyleValue> font_weight() const { return m_font_weight; }
    NonnullRefPtr<StyleValue> font_size() const { return m_font_size; }
    NonnullRefPtr<StyleValue> line_height() const { return m_line_height; }
    NonnullRefPtr<StyleValue> font_families() const { return m_font_families; }

    virtual String to_string() const override
    {
        return String::formatted("Font style: {}, weight: {}, size: {}, line_height: {}, families: {}",
            m_font_style->to_string(), m_font_weight->to_string(), m_font_size->to_string(), m_line_height->to_string(), m_font_families->to_string());
    }

private:
    FontStyleValue(NonnullRefPtr<StyleValue> font_style, NonnullRefPtr<StyleValue> font_weight, NonnullRefPtr<StyleValue> font_size, NonnullRefPtr<StyleValue> line_height, NonnullRefPtr<StyleValue> font_families)
        : StyleValue(Type::Font)
        , m_font_style(font_style)
        , m_font_weight(font_weight)
        , m_font_size(font_size)
        , m_line_height(line_height)
        , m_font_families(font_families)
    {
    }

    NonnullRefPtr<StyleValue> m_font_style;
    NonnullRefPtr<StyleValue> m_font_weight;
    NonnullRefPtr<StyleValue> m_font_size;
    NonnullRefPtr<StyleValue> m_line_height;
    NonnullRefPtr<StyleValue> m_font_families;
    // FIXME: Implement font-stretch and font-variant.
};

class IdentifierStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<IdentifierStyleValue> create(CSS::ValueID id)
    {
        return adopt_ref(*new IdentifierStyleValue(id));
    }
    virtual ~IdentifierStyleValue() override { }

    CSS::ValueID id() const { return m_id; }

    virtual bool has_auto() const override { return m_id == ValueID::Auto; }
    virtual bool has_identifier() const override { return true; }
    virtual CSS::ValueID to_identifier() const override { return m_id; }
    virtual bool has_color() const override;
    virtual Color to_color(Layout::NodeWithStyle const& node) const override;
    virtual String to_string() const override;

    virtual bool equals(StyleValue const& other) const override
    {
        if (type() != other.type())
            return false;
        return m_id == static_cast<const IdentifierStyleValue&>(other).m_id;
    }

private:
    explicit IdentifierStyleValue(CSS::ValueID id)
        : StyleValue(Type::Identifier)
        , m_id(id)
    {
    }

    CSS::ValueID m_id { CSS::ValueID::Invalid };
};

class ImageStyleValue final
    : public StyleValue
    , public ImageResourceClient {
public:
    static NonnullRefPtr<ImageStyleValue> create(AK::URL const& url, DOM::Document* document) { return adopt_ref(*new ImageStyleValue(url, document)); }
    virtual ~ImageStyleValue() override { }

    String to_string() const override { return String::formatted("Image({})", m_url.to_string()); }

    const Gfx::Bitmap* bitmap() const { return m_bitmap; }

private:
    ImageStyleValue(AK::URL const&, DOM::Document*);

    // ^ResourceClient
    virtual void resource_did_load() override;

    AK::URL m_url;
    WeakPtr<DOM::Document> m_document;
    RefPtr<Gfx::Bitmap> m_bitmap;
};

class InheritStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<InheritStyleValue> the()
    {
        static NonnullRefPtr<InheritStyleValue> instance = adopt_ref(*new InheritStyleValue);
        return instance;
    }
    virtual ~InheritStyleValue() override { }

    String to_string() const override { return "inherit"; }

private:
    InheritStyleValue()
        : StyleValue(Type::Inherit)
    {
    }
};

class InitialStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<InitialStyleValue> the()
    {
        static NonnullRefPtr<InitialStyleValue> instance = adopt_ref(*new InitialStyleValue);
        return instance;
    }
    virtual ~InitialStyleValue() override { }

    String to_string() const override { return "initial"; }

private:
    InitialStyleValue()
        : StyleValue(Type::Initial)
    {
    }
};

class LengthStyleValue : public StyleValue {
public:
    static NonnullRefPtr<LengthStyleValue> create(Length const& length)
    {
        return adopt_ref(*new LengthStyleValue(length));
    }
    virtual ~LengthStyleValue() override { }

    Length const& length() const { return m_length; }

    virtual bool has_auto() const override { return m_length.is_auto(); }
    virtual bool has_length() const override { return true; }
    virtual bool has_identifier() const override { return has_auto(); }
    virtual String to_string() const override { return m_length.to_string(); }
    virtual Length to_length() const override { return m_length; }
    virtual ValueID to_identifier() const override { return has_auto() ? ValueID::Auto : ValueID::Invalid; }

    virtual bool equals(StyleValue const& other) const override
    {
        if (type() != other.type())
            return false;
        return m_length == static_cast<LengthStyleValue const&>(other).m_length;
    }

private:
    explicit LengthStyleValue(Length const& length)
        : StyleValue(Type::Length)
        , m_length(length)
    {
    }

    virtual void visit_lengths(Function<void(CSS::Length&)> visitor) override
    {
        visitor(m_length);
    }

    Length m_length;
};

class ListStyleStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<ListStyleStyleValue> create(
        NonnullRefPtr<StyleValue> position,
        NonnullRefPtr<StyleValue> image,
        NonnullRefPtr<StyleValue> style_type)
    {
        return adopt_ref(*new ListStyleStyleValue(position, image, style_type));
    }
    virtual ~ListStyleStyleValue() override { }

    NonnullRefPtr<StyleValue> position() const { return m_position; }
    NonnullRefPtr<StyleValue> image() const { return m_image; }
    NonnullRefPtr<StyleValue> style_type() const { return m_style_type; }

    virtual String to_string() const override
    {
        return String::formatted("ListStyle position: {}, image: {}, style_type: {}", m_position->to_string(), m_image->to_string(), m_style_type->to_string());
    }

private:
    ListStyleStyleValue(
        NonnullRefPtr<StyleValue> position,
        NonnullRefPtr<StyleValue> image,
        NonnullRefPtr<StyleValue> style_type)
        : StyleValue(Type::ListStyle)
        , m_position(position)
        , m_image(image)
        , m_style_type(style_type)
    {
    }

    NonnullRefPtr<StyleValue> m_position;
    NonnullRefPtr<StyleValue> m_image;
    NonnullRefPtr<StyleValue> m_style_type;
};

class NumericStyleValue : public StyleValue {
public:
    static NonnullRefPtr<NumericStyleValue> create(float value)
    {
        return adopt_ref(*new NumericStyleValue(value));
    }

    virtual bool has_length() const override { return m_value == 0; }
    virtual Length to_length() const override { return Length(0, Length::Type::Px); }

    virtual bool has_number() const override { return true; }
    virtual float to_number() const override { return m_value; }

    float value() const { return m_value; }
    // FIXME: Store integer values separately
    i64 int_value() const { return roundf(m_value); }
    String to_string() const override { return String::formatted("{}", m_value); }

    virtual bool equals(StyleValue const& other) const override
    {
        if (type() != other.type())
            return false;
        return m_value == static_cast<NumericStyleValue const&>(other).m_value;
    }

private:
    explicit NumericStyleValue(float value)
        : StyleValue(Type::Numeric)
        , m_value(value)
    {
    }

    float m_value { 0 };
};

class OverflowStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<OverflowStyleValue> create(NonnullRefPtr<StyleValue> overflow_x, NonnullRefPtr<StyleValue> overflow_y)
    {
        return adopt_ref(*new OverflowStyleValue(overflow_x, overflow_y));
    }
    virtual ~OverflowStyleValue() override { }

    NonnullRefPtr<StyleValue> overflow_x() const { return m_overflow_x; }
    NonnullRefPtr<StyleValue> overflow_y() const { return m_overflow_y; }

    virtual String to_string() const override
    {
        return String::formatted("{} {}", m_overflow_x->to_string(), m_overflow_y->to_string());
    }

private:
    OverflowStyleValue(NonnullRefPtr<StyleValue> overflow_x, NonnullRefPtr<StyleValue> overflow_y)
        : StyleValue(Type::Overflow)
        , m_overflow_x(overflow_x)
        , m_overflow_y(overflow_y)
    {
    }

    NonnullRefPtr<StyleValue> m_overflow_x;
    NonnullRefPtr<StyleValue> m_overflow_y;
};

class StringStyleValue : public StyleValue {
public:
    static NonnullRefPtr<StringStyleValue> create(String const& string)
    {
        return adopt_ref(*new StringStyleValue(string));
    }
    virtual ~StringStyleValue() override { }

    String to_string() const override { return m_string; }

private:
    explicit StringStyleValue(String const& string)
        : StyleValue(Type::String)
        , m_string(string)
    {
    }

    String m_string;
};

class TextDecorationStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<TextDecorationStyleValue> create(
        NonnullRefPtr<StyleValue> line,
        NonnullRefPtr<StyleValue> style,
        NonnullRefPtr<StyleValue> color)
    {
        return adopt_ref(*new TextDecorationStyleValue(line, style, color));
    }
    virtual ~TextDecorationStyleValue() override { }

    NonnullRefPtr<StyleValue> line() const { return m_line; }
    NonnullRefPtr<StyleValue> style() const { return m_style; }
    NonnullRefPtr<StyleValue> color() const { return m_color; }

    virtual String to_string() const override
    {
        return String::formatted("TextDecoration line: {}, style: {}, color: {}", m_line->to_string(), m_style->to_string(), m_color->to_string());
    }

private:
    TextDecorationStyleValue(
        NonnullRefPtr<StyleValue> line,
        NonnullRefPtr<StyleValue> style,
        NonnullRefPtr<StyleValue> color)
        : StyleValue(Type::TextDecoration)
        , m_line(line)
        , m_style(style)
        , m_color(color)
    {
    }

    NonnullRefPtr<StyleValue> m_line;
    NonnullRefPtr<StyleValue> m_style;
    NonnullRefPtr<StyleValue> m_color;
};

class TransformationStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<TransformationStyleValue> create(CSS::TransformFunction transform_function, NonnullRefPtrVector<StyleValue>&& values)
    {
        return adopt_ref(*new TransformationStyleValue(transform_function, move(values)));
    }
    virtual ~TransformationStyleValue() override { }

    CSS::TransformFunction transform_function() const { return m_transform_function; }
    NonnullRefPtrVector<StyleValue> values() const { return m_values; }

    virtual String to_string() const override
    {
        return String::formatted("TransformationStyleValue");
    }

private:
    TransformationStyleValue(CSS::TransformFunction transform_function, NonnullRefPtrVector<StyleValue>&& values)
        : StyleValue(Type::Transformation)
        , m_transform_function(transform_function)
        , m_values(move(values))
    {
    }

    CSS::TransformFunction m_transform_function;
    NonnullRefPtrVector<StyleValue> m_values;
};

class UnsetStyleValue final : public StyleValue {
public:
    static NonnullRefPtr<UnsetStyleValue> the()
    {
        static NonnullRefPtr<UnsetStyleValue> instance = adopt_ref(*new UnsetStyleValue);
        return instance;
    }
    virtual ~UnsetStyleValue() override { }

    String to_string() const override { return "unset"; }

private:
    UnsetStyleValue()
        : StyleValue(Type::Unset)
    {
    }
};

class StyleValueList final : public StyleValue {
public:
    static NonnullRefPtr<StyleValueList> create(NonnullRefPtrVector<StyleValue>&& values) { return adopt_ref(*new StyleValueList(move(values))); }

    NonnullRefPtrVector<StyleValue> const& values() const { return m_values; }

    virtual String to_string() const
    {
        StringBuilder builder;
        builder.appendff("List[{}](", m_values.size());
        for (size_t i = 0; i < m_values.size(); ++i) {
            if (i)
                builder.append(',');
            builder.append(m_values[i].to_string());
        }
        builder.append(')');
        return builder.to_string();
    }

private:
    StyleValueList(NonnullRefPtrVector<StyleValue>&& values)
        : StyleValue(Type::ValueList)
        , m_values(move(values))
    {
    }

    NonnullRefPtrVector<StyleValue> m_values;
};

}
