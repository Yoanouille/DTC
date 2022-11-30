#include "front/DomPieceDisplayer.hpp"

using namespace sf;

DomPieceDisplayer::DomPieceDisplayer(App &app, int x, int y, DomPiece &p) : PieceDisplayer{app,x,y, p}
{   
    Color c{255,255,255,255};
    this->setFillColor(c);
}

DomPieceDisplayer::~DomPieceDisplayer() {}

void DomPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
}

void DomPieceDisplayer::loop_event()
{

}