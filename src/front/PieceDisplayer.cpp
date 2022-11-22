#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(Menu &m, int x, int y) : menu{m}, coordinates{x,y} {}

PieceDisplayer::~PieceDisplayer() {}

// PAS BON
// void PieceDisplayer::loop_event()
// {
//     Event event;
//     while (menu.pollEvent(event))
//     {
//         if (event.type == sf::Event::MouseWheelMoved)
//         {
//             if (event.mouseWheel.delta < 0)
//             {
//                 piece->rotate(false);
//                 rotate(-90.0);
//             }
//             else
//             {
//                 piece->rotate(true);
//                 rotate(90.0);
//             }
//         }
//     }
// }

void PieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{

}