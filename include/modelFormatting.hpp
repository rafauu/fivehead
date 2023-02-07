#pragma once

#include "model.hpp"

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <array>
#include <algorithm>


namespace Fivehead
{

template <typename T>
constexpr char formatColor(T color);

template <>
constexpr char formatColor<ModelTypes::CodeColor>(ModelTypes::CodeColor color)
{
    struct MappingType 
    {
        ModelTypes::CodeColor color;
        char output;
    };

    constexpr std::array mapping{
        MappingType{ModelTypes::CodeColor::Red,    'R'},
        MappingType{ModelTypes::CodeColor::Green,  'G'},
        MappingType{ModelTypes::CodeColor::Yellow, 'Y'},
        MappingType{ModelTypes::CodeColor::Blue,   'B'},
        MappingType{ModelTypes::CodeColor::Pink,   'P'}
    };
    auto it = std::find_if(std::begin(mapping), std::end(mapping), [=](auto entry){ return entry.color == color; });
    return it != std::end(mapping) ? it->output : ' ';
}

template <>
constexpr char formatColor<ModelTypes::KeyColor>(ModelTypes::KeyColor color)
{
    struct MappingType 
    {
        ModelTypes::KeyColor color;
        char output;
    };

    constexpr std::array mapping{
        MappingType{ModelTypes::KeyColor::Black, 'B'},
        MappingType{ModelTypes::KeyColor::White, 'W'}
    };
    auto it = std::find_if(std::begin(mapping), std::end(mapping), [=](auto entry){ return entry.color == color; });
    return it != std::end(mapping) ? it->output : ' ';
}

#define ENABLE_FORMATTING(Type, ...) \
template <> class fmt::formatter<Type> { \
public: \
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); } \
    template <typename Context> \
    constexpr auto format(const Type& value, Context& ctx) const \
    { \
        return format_to(ctx.out(), __VA_ARGS__); \
    } \
}; \

}

ENABLE_FORMATTING(Fivehead::ModelTypes::CodeColor, "{}", formatColor(value))
ENABLE_FORMATTING(Fivehead::ModelTypes::KeyColor, "{}", formatColor(value))

