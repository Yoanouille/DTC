#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(App &app, int x, int y) : app{app}, state{0}, coordinates{x, y} {}

PieceDisplayer::~PieceDisplayer() {}

void PieceDisplayer::setPos(int x, int y)
{
    coordinates.x = x;
    coordinates.y = y;
}

void PieceDisplayer::nextState()
{
    if(state < 1) state++;
}

bool PieceDisplayer::isFinalState()
{
    return (state == 1);
}

int PieceDisplayer::getState() const
{
    return state;
}

sf::Vector2i PieceDisplayer::getCoord() const
{
    return coordinates;
}

void PieceDisplayer::handleClick(sf::Vector2f &mouse, Player *p, int player, int scl)
{
    //nothing
}

void PieceDisplayer::removeHandle(Player *p, int player)
{
    //nothing
}
