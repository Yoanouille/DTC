#include "back/CarcPiece.hpp"

#include <iostream>
#include <vector>

using namespace std;

/**
 * Constructor 
 * 
 * It Hardcoding...
 * We'll follow the order on CPiece.png line by line.
 * 
 * Notice that between 2 and 12, pieces with even id have a shields (bonus points)
 */
CarcPiece::CarcPiece(int d) : id{d}, pawn_center{-1}, color_center{-1}, bonus{0}
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            pawn[i][j] = -1;
            color_border[i][j] = -1;
        }
    }

    switch(id){
        case(0): 
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            center = Abbaye;
            break;
        
        case(1): 
            for (size_t i = 0; i < 4 ; i++)
                for (size_t j = 0; j < 3; j++) 
                    border[i][j] = Field;

            border[2][1] = Road;
            center = Abbaye;
            break;

        case(2): 
            for (size_t i = 0; i < 4 ; i++)
                for (size_t j = 0; j < 3; j++) 
                    border[i][j] = Town;

            center = Town;
            break;

        case(3): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = Town;
            break;

        case(4):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = Town;
            break;

        case(5): 
           for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }
            
            border[2][1] = Road;
            center = Town;
            break;

        case(6):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }
                
            border[2][1] = Road;
            center = Town;
            break;

        case(7): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = Field;
            break;

        case(8): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            center = Field;
            break;

        case(9):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[2][1] = Road;
            border[3][1] = Road;
            center = Road;
            break;

        case(10):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            border[2][1] = Road;
            border[3][1] = Road;
            center = Road;
            break;

        case(11): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = Town;
            break;

        case(12): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = Town;
            break;

        case(13): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = Field;
            break;

        case(14): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Town;
                border[3][j] = Field;
            }

            center = Field;
            break;

        case(15): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = Field;
            break;

        case(16): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[1][1] = Road;
            border[2][1] = Road;
            center = Road;
            break;

        case(17): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[3][1] = Road;
            border[2][1] = Road;
            center = Road;
            break;

        case(18):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[3][1] = Road;
            border[2][1] = Road;
            border[1][1] = Road;
            center = Crossroad;
            break;

        case(19): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[3][1] = Road;
            border[1][1] = Road;
            center = Road;
            break;

        case(20):
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            
            border[0][1] = Road;
            border[2][1] = Road;
            center = Road;
            break;

        case(21):
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            
            border[1][1] = Road;
            border[2][1] = Road;
            center = Road;
            break;
            
        case(22):
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            
            border[1][1] = Road;
            border[2][1] = Road;
            border[3][1] = Road;
            center = Crossroad;
            break;

        case(23): 
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;

            for(size_t i = 0; i < 4; i++)
                border[i][1] = Road;

            center = Crossroad;
            break;

        case(24):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            
            border[3][1] = Road;
            border[1][1] = Road;
            center = Road;
            break;
    }
}

CarcPiece::~CarcPiece() {}

const int CarcPiece::getId() const{
    return id;
}

bool CarcPiece::getBonus() const
{
    return bonus;
}

bool CarcPiece::connectable(Piece &p, int pDir)
{
    CarcPiece &p1 = (CarcPiece &)p;
    for(int i = 0; i < 3; i++)
        if (border[(direction + pDir + 2)%4][i] != p1.border[((pDir + p1.direction)) %4][2 - i])
            return false;

    return true;
    
}

void CarcPiece::getConnectColor(int *t) const
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = border[(i + direction) % 4][1];
    }
}

string CarcPiece::toString() const
{
    string s{" "};
    for (size_t j = 0; j < 3; j++)
        s += to_string(border[direction][j]) + " ";
    s += "\n";

    for (size_t j = 0; j < 3; j++)
        s += to_string(border[(direction + 1) % 4][2 - j]) + "  " + (j == 1 ? to_string(center) : " ") + "  " + to_string(border[(direction + 3) % 4][j]) + "\n";
    s += " ";
    for (size_t j = 0; j < 3; j++)
        s += to_string(border[(direction + 2) % 4][2 - j]) + " ";

  return s;
}

bool CarcPiece::playOnPiece(int dir, int player)
{
    if(dir >= 0 && dir <= 4 && pawn[(dir + direction) % 4][1] == -1) 
    {
        pawn[(dir + direction) % 4][1] = player;
        return true;
    }
    if(dir == 5 && pawn_center == -1)
    {
        pawn_center = player;
        return true;
    }

    return false;
}

void CarcPiece::getPlayPawn(int *t) const
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = pawn[(i + direction) % 4][1];
    }
    t[4] = pawn_center;
}

int CarcPiece::getCenter() const
{
    return center;
}

void CarcPiece::removePawn(int d)
{
    pawn[(d + direction) % 4][1] = -1;
}

void CarcPiece::beginExplore(int i, int j, bool cent, CarcType t)
{
    explore((i + direction) % 4,j,cent,t);
}

void CarcPiece::printColor()
{
    string s{" "};
    for (size_t j = 0; j < 3; j++)
        s += to_string(color_border[direction][j]) + " ";
    s += "\n";

    for (size_t j = 0; j < 3; j++)
        s += to_string(color_border[(direction + 1) % 4][2 - j]) + "  " + (j == 1 ? to_string(color_center) : " ") + "  " + to_string(color_border[(direction + 3) % 4][j]) + "\n";
    s += " ";
    for (size_t j = 0; j < 3; j++)
        s += to_string(color_border[(direction + 2) % 4][2 - j]) + " ";   
    cout << s << endl; 
}

void CarcPiece::explore(int i, int j, bool cent, CarcType t)
{
    //cout << i << " " << j << " " << cent << " " << t << endl;
    if(color_border[i][j] == 1) return;
    if(cent)
    {
        color_center = 1;

        for(int i = 0; i < 4; i++)
            if(color_border[i][1] == -1 && border[i][1] == t) explore(i, 1, false, t);


    } 
    else 
    {
        color_border[i][j] = 1;
        if(color_center == -1)
        {
            if(center == t) explore(0,0,true,t);
        }

        if(j == 1)
        {
            
            if(color_border[i][0] == -1 && border[i][0] == t) explore(i, 0, false, t);
            if(color_border[i][2] == -1 && border[i][2] == t) explore(i, 2, false, t);
        } else if(j == 0)
        {
            if(color_border[i][1] == -1 && border[i][1] == t) explore(i, 1, false, t);
            if(color_border[(i + 1) % 4][2] == -1 && border[(i + 1) % 4][2] == t) explore((i + 1) % 4, 2, false, t);
        } else 
        {
            if(color_border[i][1] == -1 && border[i][1] == t) explore(i, 1, false, t);
            if(color_border[(i + 3) % 4][0] == -1 && border[(i + 3) % 4][0] == t) explore((i + 3) % 4, 0, false, t);
        }
    }
}

void CarcPiece::cleanColor()
{
    cout << "LAVAGE" << endl;
    color = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 3; j++)
            color_border[i][j] = -1;
    color_center = -1;
}

void CarcPiece::removeAllPawn()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(color_border[i][j] != -1)
            {
                pawn[i][j] = -1;
            }
        }
    }
    if(color_center == 1) pawn_center = -1;
}

int CarcPiece::getColor(int i, int j, bool cent) const
{
    if(cent) return color_center;
    return color_border[(i + direction) % 4][j];
}

int CarcPiece::getType(int i, int j, bool cent) const
{
    if(cent) return center;
    //cout << "type : " << i << " " << j << " " << border[(i + direction) % 4][j] << endl;
    return border[(i + direction) % 4][j];
}

bool CarcPiece::hasPawn()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(pawn[i][j] != -1) return true;
        }
    }
    return (pawn_center != -1);
}

Pos CarcPiece::getPosPawn() const
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(pawn[i][j] != -1) return {i, j};
        }
    }
    if(pawn_center != -1) return {4,3};
    return {-1,-1};
}


void CarcPiece::putPawn(int i, int j, bool center, int player)
{
    if(center) pawn_center = player;
    pawn[(i + direction) % 4][j] = player;
}


int CarcPiece::getNbPawn(int *t, int nb_player)
{
    int nb = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(color_border[i][j] == 1 && pawn[i][j] != -1)
            {
                color_border[i][j]++;
                t[pawn[i][j]]++; 
                nb++;
            }
        }
    }
    if(color_center == 1 && pawn_center != -1) 
    {
        color_center++;
        nb++;
    } 
    return nb;
}

vector<Pos> CarcPiece::getNextDir()
{
    vector<Pos> next_dir{};
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            //! PAS SUR ICI DU (i+3+direction) (peut etre (i+direction) seulement)
            // * Checked : normalement ok
            if(color_border[i][j] != -1) 
            {
                //cout << (i + direction) % 4 << " " << j << endl;
                next_dir.push_back({(i - direction + 4) % 4, j});
            }
        }
    }
    return next_dir;
}