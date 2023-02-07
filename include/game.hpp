#pragma once

#include "model.hpp"
#include "controller.hpp"
#include "ui.hpp"
#include "logic.hpp"

class Game
{
private:
    Model model{};
    Controller controller{model};
    Ui ui{
        .boardView = Ui::BoardView{model},
        .user = Ui::User{}
    };
    Logic logic{};

public:
    Game()
    {
        ui.user.setCodemakerCode.connect(&Controller::newCodemakerCode, &controller);
        ui.user.setCodebrakerCode.connect(&Controller::newCodebrakerCode, &controller);
        model.dataChanged.connect(&Ui::BoardView::renderData, &ui.boardView);
        controller.checkPatterns.connect(&Logic::comparePatterns, &logic);
        logic.setCodebrakerKey.connect(&Controller::newCodebrakerKey, &controller);
    }
    void runSimulation()
    {
        using enum Model::CodeColor;
        ui.user.setCodemakerCode(Model::Code{Green, Blue, Red, Pink});

        ui.user.setCodebrakerCode(Model::Code{Yellow, Yellow, Blue,  Blue});
        ui.user.setCodebrakerCode(Model::Code{Pink,   Red,    Red,   Yellow});
        ui.user.setCodebrakerCode(Model::Code{Green,  Pink,   Green, Yellow});
        ui.user.setCodebrakerCode(Model::Code{Red,    Red,    Pink,  Yellow});
        ui.user.setCodebrakerCode(Model::Code{Blue,   Red,    Green, Pink});
        ui.user.setCodebrakerCode(Model::Code{Green,  Blue,   Red,   Pink});
    }
};
