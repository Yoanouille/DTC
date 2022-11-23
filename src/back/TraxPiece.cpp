#include "back/TraxPiece.hpp"
using namespace std;

/**
 * Constructor
 * There are 2 kinds of TraxPiece : Recto(Crossroad) and Verso
 * The piece is on Recto by default.
 */
TraxPiece::TraxPiece() : tab{false, true, false, true}, recto{true} {}

/** Destructor */
TraxPiece ::~TraxPiece() {}

/** Getter */
bool TraxPiece::isRecto() const { return recto; }

/** Overriden function */
int TraxPiece::connectable(Piece &p, int pDir) { return true; }

/** Overriden function*/
int TraxPiece::getEarnedValue(Piece &p, int pDir) { return 0; }

/**
 * Flip the TraxPiece
 */
void TraxPiece::flip()
{
    if (recto)
    {
        tab[0] = true;
        tab[1] = false;
    }
    else
    {
        tab[0] = false;
        tab[1] = true;
    }

    recto = !recto;
}

/**
 * toString method
 * create the following string
 * ---- Trax : Recto/Verso ----
 *  a
 * b c
 *  d
 */
string TraxPiece::toString() const
{
    string s{" "};
    s += to_string(tab[0]) + "\n" + to_string(tab[1]) + " " + to_string(tab[3]) + "\n " + to_string(tab[2]);
    return s;
}
