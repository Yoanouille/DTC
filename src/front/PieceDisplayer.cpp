#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(Menu &m, Piece &p, int x, int y) : menu{m}, piece{p}, coordinates{x, y} {}

PieceDisplayer::~PieceDisplayer() {}

/**
 * Rotate the Piece
 * Adapt the view to the rotation 
 */
void PieceDisplayer::rotate(bool clockwise)
{
    piece.rotate(clockwise);
    if(clockwise)
        rotate(90.0);
    else 
        rotate(-90.0);
}