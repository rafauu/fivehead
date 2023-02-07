#pragma once

#include "property.hpp"

#include <cstdint>
#include <limits>
#include <array>
#include <vector>
#include <sigslot/signal.hpp>


namespace Fivehead
{

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

struct Model : ModelTypes
{
    Property<Code> codemakerCode{[this]{ dataChanged(); }};
    Property<std::vector<Code>> codebrakerCodes{[this]{ dataChanged(); }};
    Property<std::vector<Key>> codebrakerKeys{[this]{ dataChanged(); }};

    sigslot::signal<> dataChanged;
};

}

