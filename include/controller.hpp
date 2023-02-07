#pragma once

#include "model.hpp"
#include <sigslot/signal.hpp>

namespace Fivehead
{

class Controller
{
public:
    explicit Controller(Model&);
    void newCodemakerCode(Model::Code);
    void newCodebrakerCode(Model::Code);
    void newCodebrakerKey(Model::Key);

    sigslot::signal<Model::CodesPair> checkPatterns;

private:
    Model& model;
};

}

