#include "back/Piece.hpp"
using namespace std;

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
 * Rotate the Piece following a direction
 * that is clockwise or counterclockwise
 *
 * @param clockwise A boolean equals to true if the rotation is in clockwise direction.
 */
void Piece::rotate(bool clockwise)
{
    if (clockwise)
        direction = (direction + 3) % 4;
    else
        direction = (direction + 1) % 4;
}

/**
 * Printing function
 */
ostream &operator<<(ostream &out, const Piece &p)
{
    out << p.toString() << endl;
    return out;
}