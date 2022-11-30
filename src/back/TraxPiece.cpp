#include "back/TraxPiece.hpp"
using namespace std;
#include <iostream>

/**
 * Constructor
 * There are 2 kinds of TraxPiece : Recto(Crossroad) and Verso
 * The piece is on Recto by default.
 */
TraxPiece::TraxPiece() : tab{false, true, false, true}, recto{true}, color_dir{-1,-1,-1,-1} {}

/** Destructor */
TraxPiece ::~TraxPiece() {}

/** Getter */
bool TraxPiece::isRecto() const { return recto; }

/** Overriden function */
bool TraxPiece::connectable(Piece &p, int pDir)
{
    //cout << direction << " " << pDir << endl;
    //cout << ((TraxPiece &)p).direction << endl;
    //cout << tab[(direction + pDir)%4] << " " << ((TraxPiece &)p).tab[((pDir + ((TraxPiece &)p).direction) + 2) %4] << endl;
    return tab[(direction + pDir + 2)%4] == ((TraxPiece &)p).tab[((pDir + ((TraxPiece &)p).direction)) %4];
}

/** Overriden function*/
int TraxPiece::getEarnedValue(Piece &p, int pDir) { 
    TraxPiece &p1 = (TraxPiece &)p;
    int col = 0;
    if(tab[(direction + pDir + 2)%4]) col = 1;
    p1.color_dir[pDir] = col;
    this->color_dir[(pDir + 2)%4] = col;
    return 0; 
}

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
    s += to_string(tab[direction]) + "\n" + to_string(tab[(direction + Direction::LEFT) % 4]) + " " + to_string(tab[(direction + Direction::RIGHT) % 4]) + "\n " + to_string(tab[(direction + Direction::DOWN) % 4]);
    return s;
}

void TraxPiece::getConnectColor(int *t)
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = color_dir[i];   
    }
}
