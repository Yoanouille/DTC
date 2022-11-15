#include "back/Piece.hpp"

/**
 * Destructor
 * Defined to fix the following warning :
 * " deleting object of abstract class type ‘Piece’ which has non-virtual destructor
 *   will cause undefined behavior "
 * that appeared in Sack's destructor.
 */
Piece::~Piece() {}

int Piece::getDirection() const
{
    return direction;
}

int Piece::getColor() const
{
    return color;
}

/**
 * Rotate the Piece
 */
void Piece::rotate()
{
    direction = (direction + 1) % 4;
}