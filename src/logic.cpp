#include "logic.hpp"


namespace Fivehead
{

void Logic::comparePatterns(Model::CodesPair codes)
{
    Model::Key key;

    for (auto i = 0u; i < codes.guess.size(); ++i)
    {
        if (codes.guess[i] == codes.pattern[i])
        {
            key.push_back(Model::KeyColor::Black);
            codes.guess[i] = Model::CodeColor::Invalid;
            codes.pattern[i] = Model::CodeColor::Invalid;
        }
    }

    for (auto i = 0u; i < codes.pattern.size(); ++i)
    {
        if (codes.pattern[i] != Model::CodeColor::Invalid)
        {
            auto it = std::find(std::begin(codes.guess), std::end(codes.guess), codes.pattern[i]);
            if (it != std::end(codes.guess))
            {
                key.push_back(Model::KeyColor::White);
                codes.guess[std::distance(std::begin(codes.guess), it)] = Model::CodeColor::Invalid;
            }
        }
    }

    setCodebrakerKey(key);
}

}
