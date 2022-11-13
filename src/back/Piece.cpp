#include "back/Piece.hpp"

int Piece::getDirection() const
{
    return direction;
}

int Piece::getColor() const
{
    return color;
}

void Piece::rotate()
{
    direction = (direction + 1) % 4;
}