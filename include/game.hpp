#pragma once

#include <memory>


namespace Fivehead
{

class Model;
class Controller;
class Ui;
class Logic;

class Game
{
public:
    Game();
    ~Game();
    void runSimulation();

private:
    std::unique_ptr<Model> model;
    std::unique_ptr<Controller> controller;
    std::unique_ptr<Ui> ui;
    std::unique_ptr<Logic> logic;
};

}

