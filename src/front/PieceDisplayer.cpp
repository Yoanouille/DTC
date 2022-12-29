#include "front/PieceDisplayer.hpp"
using namespace sf;

/** Constructor */
PieceDisplayer::PieceDisplayer(App &app, int x, int y) : app{app}, state{0}, coordinates{x, y} {}

/** Destructor */
PieceDisplayer::~PieceDisplayer() {}

/**
 * Set the position of the displayer.
 * 
 * @param x The abscissa
 * @param y The ordinate 
 */
void PieceDisplayer::setPos(int x, int y)
{
    coordinates.x = x;
    coordinates.y = y;
}

/** Increment the state  */
void PieceDisplayer::nextState()
{
    if(state < 1) state++;
}

/** Test if the state is the final state */
bool PieceDisplayer::isFinalState()
{
    return (state == 1);
}

/** Getter : state */
int PieceDisplayer::getState() const { return state; }

/** Getter : coordinates */
sf::Vector2i PieceDisplayer::getCoord() const { return coordinates; }

void PieceDisplayer::handleClick(sf::Vector2f &mouse, Player *p, int player, int scl) {}

void PieceDisplayer::removeHandle(Player *p, int player) {}
