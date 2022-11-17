#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::~PieceDisplayer() {}

void PieceDisplayer::loop_event()
{
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == sf::Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta < 0)
            {
                // TODO : rotate trigo
            }
            else
            {
                // TODO : rotate clock
            }
        }
    }
}