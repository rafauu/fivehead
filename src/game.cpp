#include "game.hpp"

#include "model.hpp"
#include "controller.hpp"
#include "ui.hpp"
#include "logic.hpp"


namespace Fivehead
{

Game::Game() :
    model{std::make_unique<Model>()},
    controller{std::make_unique<Controller>(*model)},
    ui{std::make_unique<Ui>(Ui{Ui::BoardView{*model}, Ui::User{}})},
    logic{std::make_unique<Logic>()}
{
    ui->user.setCodemakerCode.connect(&Controller::newCodemakerCode, controller.get());
    ui->user.setCodebrakerCode.connect(&Controller::newCodebrakerCode, controller.get());
    model->dataChanged.connect(&Ui::BoardView::renderData, &ui->boardView);
    controller->checkPatterns.connect(&Logic::comparePatterns, logic.get());
    logic->setCodebrakerKey.connect(&Controller::newCodebrakerKey, controller.get());
}

Game::~Game() = default;

void Game::runSimulation()
{
    using enum Model::CodeColor;
    ui->user.setCodemakerCode(Model::Code{Green, Blue, Red, Pink});

    ui->user.setCodebrakerCode(Model::Code{Yellow, Yellow, Blue,  Blue});
    ui->user.setCodebrakerCode(Model::Code{Pink,   Red,    Red,   Yellow});
    ui->user.setCodebrakerCode(Model::Code{Green,  Pink,   Green, Yellow});
    ui->user.setCodebrakerCode(Model::Code{Red,    Red,    Pink,  Yellow});
    ui->user.setCodebrakerCode(Model::Code{Blue,   Red,    Green, Pink});
    ui->user.setCodebrakerCode(Model::Code{Green,  Blue,   Red,   Pink});
}

}

