#pragma once

#include <sigslot/signal.hpp>
#include "model.hpp"

struct Ui
{
    class BoardView
    {
    public:
        explicit BoardView(const Model& model) : model{model} {}

        void renderData()
        {
            //TODO: render only data that has changed since last render
        }

    private:
        const Model& model;
    };

    class User
    {
    public:
        sigslot::signal<Model::Code> setCodebrakerCode;
        sigslot::signal<Model::Code> setCodemakerCode;
    };

    BoardView boardView;
    User user;
};
