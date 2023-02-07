#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <sigslot/signal.hpp>
#include <array>
#include <type_traits>
#include <functional>


template <typename T>
class Property
{
private:
    T data;
    std::function<void()> callable;

public:
    template <typename Callable>
    explicit Property(Callable callable) : callable{callable} {}

    const T& get() const
    {
        return data;
    }

    template <typename U>
    void set(U&& newData)
    {
        const bool dataChanged = (newData != data);
        data = std::forward<U>(newData);
        if (dataChanged)
            callable();
    }
};


struct ModelTypes
{
private:
    using EnumType = std::uint8_t;
public:
    enum class CodeColor : EnumType
    {
        Red,
        Green,
        Yellow,
        Blue,
        Pink,
        Invalid = std::numeric_limits<EnumType>::max()
    };
    enum class KeyColor : EnumType
    {
        White,
        Black
    };
    using Code = std::array<CodeColor, 4>;
    using Key = std::vector<KeyColor>;

    struct CodesPair
    {
        Code guess;
        Code pattern;
    };
};

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
    constexpr auto parse (format_parse_context& ctx) { return ctx.begin(); } \
    template <typename Context> \
    constexpr auto format (const Type& value, Context& ctx) const \
    { \
        return format_to(ctx.out(), __VA_ARGS__); \
    } \
}; \

ENABLE_FORMATTING(ModelTypes::CodeColor, "{}", formatColor(value))
ENABLE_FORMATTING(ModelTypes::KeyColor, "{}", formatColor(value))

struct Model : ModelTypes
{
    Property<Code> codemakerCode{[this]{ dataChanged(); }};
    Property<std::vector<Code>> codebrakerCodes{[this]{ dataChanged(); }};
    Property<std::vector<Key>> codebrakerKeys{[this]{ dataChanged(); }};

    sigslot::signal<> dataChanged;
};
