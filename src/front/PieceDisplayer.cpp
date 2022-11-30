#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(App &app, int x, int y, Piece &p) : app{app}, coordinates{x, y},  piece{p} {}

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