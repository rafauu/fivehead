#pragma once

#include "model.hpp"
#include <sigslot/signal.hpp>


namespace Fivehead
{

struct Logic
{
    void comparePatterns(Model::CodesPair);

    sigslot::signal<Model::Key> setCodebrakerKey;
};

}

