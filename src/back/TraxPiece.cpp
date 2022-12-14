#include "back/TraxPiece.hpp"
using namespace std;
#include <iostream>
#include <vector>

/**
 * Constructor
 * There are 2 kinds of TraxPiece : Recto(Crossroad) and Verso
 * The piece is on Recto by default.
 */
TraxPiece::TraxPiece() : tab{true, false, true, false}, recto{true}, color_dir{-1,-1,-1,-1} {}

/** Destructor */
TraxPiece ::~TraxPiece() {}

/** Getter */
bool TraxPiece::isRecto() const { return recto; }

/** Overriden function */
bool TraxPiece::connectable(Piece &p, int pDir)
{
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
        tab[1] = true;
        tab[2] = false;
        tab[3] = false;
    }
    else
    {
        tab[0] = true;
        tab[1] = false;
        tab[2] = true;
        tab[3] = false;
    }

    recto = !recto;
    direction = 0;
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

void TraxPiece::getConnectColor(int *t) const
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = color_dir[i];   
    }
}

bool TraxPiece::forcedMove(vector<TraxPiece *> tabp)
{
    int dir[4] = {-1,-1,-1,-1};

    for(int i = 0; i < 4; i++)
    {
        if(tabp[i] != nullptr)
        {
            dir[i] = tabp[i]->tab[(tabp[i]->direction + i + 2)%4];
        }
    }

    int count = 0;
    
    for(int i = 0; i < 4; i++)
    {
        if(dir[i] != -1)
        {
            for(int j = i + 1; j < 4; j++)
            {
                if(dir[j] != -1 && dir[i] == dir[j])
                {
                    count++;
                }
            }
        }
    }

    return count >= 2;

}
