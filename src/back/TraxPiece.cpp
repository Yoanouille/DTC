#include "back/TraxPiece.hpp"
using namespace std;

/**
 * Constructor
 * There are 2 kinds of TraxPiece : Recto(Crossroad) and Verso
 * The piece is on Recto by default.
 */
TraxPiece::TraxPiece() : tab{false, true, false, true}, isRecto{true} {}

/** Destructor */
TraxPiece ::~TraxPiece() {}

/** Overriden function */
int TraxPiece::connectable(Piece &p, int pDir) { return true; }

/** Overriden function*/
int TraxPiece::getEarnedValue(Piece &p, int pDir) { return 0; }

/**
 * Flip the TraxPiece
 */
void TraxPiece::flip()
{
    if (isRecto)
    {
        tab[0] = true;
        tab[1] = false;
    }
    else
    {
        tab[0] = false;
        tab[1] = true;
    }

    isRecto = !isRecto;
}

/**
 * Printing function
 */
ostream &operator<<(ostream &out, const TraxPiece &p)
{

    if (p.isRecto)
        out << "Recto" << endl;
    else
        out << "Verso" << endl;

    out << "[ ";
    for (bool b : p.tab)
    {
        out << b << " ";
    }
    out << "]";

    return out;
}