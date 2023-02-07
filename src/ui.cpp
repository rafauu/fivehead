#include "ui.hpp"


namespace Fivehead
{

Ui::BoardView::BoardView(const Model& model) :
    model{model}
{}

void Ui::BoardView::renderData()
{
    //TODO: render only data that has changed since last render
    (void)model;
}

}

