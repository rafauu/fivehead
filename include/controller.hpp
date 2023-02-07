#pragma once

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <sigslot/signal.hpp>
#include "model.hpp"


class Controller
{
public:
    explicit Controller(Model& model) : model{model} {}

    void newCodemakerCode(Model::Code code)
    {
        fmt::print("Controller::newCodemakerCode: {}\n", code);

        model.codemakerCode.set(code);
    }

    void newCodebrakerCode(Model::Code code)
    {
        fmt::print("Controller::newCodebrakerCode: {}\n", code);

        auto codes = model.codebrakerCodes.get();
        codes.push_back(code);
        model.codebrakerCodes.set(codes);

        checkPatterns(
            Model::CodesPair{
                .guess = model.codebrakerCodes.get().back(),
                .pattern = model.codemakerCode.get()
            }
        );
        
    }

    void newCodebrakerKey(Model::Key key)
    {
        fmt::print("Controller::newCodebrakerKey: {}\n", key);

        auto keys = model.codebrakerKeys.get();
        keys.push_back(key);
        model.codebrakerKeys.set(keys);
    }

    sigslot::signal<Model::CodesPair> checkPatterns;

private:
    Model& model;
};
