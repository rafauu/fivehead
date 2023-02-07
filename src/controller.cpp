#include "controller.hpp"

#include "modelFormatting.hpp"

#include <sigslot/signal.hpp>


namespace Fivehead
{

Controller::Controller(Model& model) :
    model{model}
{}

void Controller::newCodemakerCode(Model::Code code)
{
    fmt::print("Controller::newCodemakerCode: {}\n", code);

    model.codemakerCode.set(code);
}

void Controller::newCodebrakerCode(Model::Code code)
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

void Controller::newCodebrakerKey(Model::Key key)
{
    fmt::print("Controller::newCodebrakerKey: {}\n", key);

    auto keys = model.codebrakerKeys.get();
    keys.push_back(key);
    model.codebrakerKeys.set(keys);
}

}

