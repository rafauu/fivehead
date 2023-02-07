#pragma once

#include <sigslot/signal.hpp>
#include "model.hpp"


namespace Fivehead
{

struct Ui
{
    class BoardView
    {
    public:
        explicit BoardView(const Model&);
        void renderData();
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

}

