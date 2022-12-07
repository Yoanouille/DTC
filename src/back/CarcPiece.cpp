#include "back/CarcPiece.hpp"

#include <iostream>

using namespace std;

CarcPiece::CarcPiece(int i) : id{i}, color_dir{-1,-1,-1,-1}
{
    //TODO Générer la pièce en fonction de l'id
}

CarcPiece::~CarcPiece()
{

}

bool CarcPiece::connectable(Piece &p, int pDir)
{
    CarcPiece &p1 = (CarcPiece &)p;
    for(int i = 0; i < 3; i++)
    {
        border[(direction + pDir + 2)%4][i] == p1.border[((pDir + p1.direction)) %4][2 - i];
    }
}

int CarcPiece::getEarnedValue(Piece &p, int pDir) 
{
    CarcPiece &p1 = (CarcPiece &)p;
    int col = 0;
    col = border[(direction + pDir + 2)%4][1];
    p1.color_dir[pDir] = col;
    this->color_dir[(pDir + 2)%4] = col;
    return 0;
}

void CarcPiece::getConnectColor(int *t) const
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = color_dir[i];   
    }
}

string CarcPiece::toString() const
{
    string s{" "};
    for (size_t j = 0; j < 3; j++)
        s += to_string(border[0][j]) + " ";
    s += "\n";

    for (size_t j = 0; j < 3; j++)
        s += to_string(border[1][2 - j]) + "  " + (j == 1 ? to_string(center) : " ") + "  " + to_string(border[3][j]) + "\n";
    s += " ";
    for (size_t j = 0; j < 3; j++)
        s += to_string(border[2][2 - j]) + " ";

  return s;
}