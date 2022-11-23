#include "front/TraxPieceDisplayer.hpp"
using namespace sf;

/**
 * Constructor
 *
 */
TraxPieceDisplayer::TraxPieceDisplayer(Menu &m, int x, int y) : PieceDisplayer(m, x, y)
{
    image.loadFromFile("resources/images/traxR.png");
    sprite.setTexture(image);
}

TraxPieceDisplayer::~TraxPieceDisplayer() {}

void TraxPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{
    Vector2f v = {coordinates.x * scl, coordinates.y * scl};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({scl, scl});
    if(this->getGlobalBounds().intersects(board.getGlobalBounds()))
    {
        menu.draw(*this);
    }
}

// The Piece inherts rotate() from Shape
void TraxPieceDisplayer::loop_event()
{
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta < 0)
            {
                piece->rotate(false);
                rotate(-90.0);
            }
            else
            {
                piece->rotate(true);
                rotate(90.0);
            }
        }

        // TODO : flip the piece but how ?
    }
}