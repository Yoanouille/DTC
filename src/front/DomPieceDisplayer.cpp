#include "front/DomPieceDisplayer.hpp"

using namespace sf;

DomPieceDisplayer::DomPieceDisplayer(Menu &m, int x, int y, DomPiece &p) : PieceDisplayer{m,x,y, p}
{   
    Color c{255,255,255,255};
    this->setFillColor(c);
}

DomPieceDisplayer::~DomPieceDisplayer() {}

void DomPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{
    Vector2f v{coordinates.x * scl, coordinates.y * scl};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({scl, scl});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        menu.draw(*this);
}

void DomPieceDisplayer::loop_event()
{

}