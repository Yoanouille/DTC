#include "front/TraxPieceDisplayer.hpp"
using namespace sf;

/**
 * Constructor
 *
 */
TraxPieceDisplayer::TraxPieceDisplayer(Menu &m) : PieceDisplayer(m)
{
    image.loadFromFile("resources/images/traxR.png");
    sprite.setTexture(image);
}

TraxPieceDisplayer::~TraxPieceDisplayer() {}

void TraxPieceDisplayer::render()
{
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