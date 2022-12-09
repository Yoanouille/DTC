#include "back/CarcPiece.hpp"

#include <iostream>

using namespace std;

/**
 * Constructor 
 * 
 * It Hardcoding...
 * We'll follow the order on CPiece.png line by line.
 * 
 * Notice that between 2 and 12, pieces with even id have a shields (bonus points)
 */
CarcPiece::CarcPiece(int i) : id{i}, play{-1,-1,-1,-1}, play_center{-1}, color_dir{-1,-1,-1,-1}
{
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

            center = DownTown;
            break;

        case(3): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = DownTown;
            break;

        case(4):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = DownTown;
            break;

        case(5): 
           for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }
            
            border[2][1] = Road;
            center = DownTown;
            break;

        case(6):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }
                
            border[2][1] = Road;
            center = DownTown;
            break;

        case(7): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = None;
            break;

        case(8): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }
            center = None;
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
            center = None;
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
            center = None;
            break;

        case(11): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = None;
            break;

        case(12): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;
            }

            center = None;
            break;

        case(13): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = None;
            break;

        case(14): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Town;
                border[3][j] = Field;
            }

            center = None;
            break;

        case(15): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;
            }

            center = None;
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
            center = None;
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
            center = None;
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
            center = None;
            break;

        case(20):
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            
            border[0][1] = Road;
            border[2][1] = Road;
            center = None;
            break;

        case(21):
            for(size_t i = 0; i < 4; i++)
                for(size_t j = 0; j < 3; j++)
                    border[i][j] = Field;
            
            border[1][1] = Road;
            border[2][1] = Road;
            center = None;
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
            center = None;
            break;
    }
}

CarcPiece::~CarcPiece() {}

const int CarcPiece::getId() const{
    return id;
}

bool CarcPiece::connectable(Piece &p, int pDir)
{
    CarcPiece &p1 = (CarcPiece &)p;
    for(int i = 0; i < 3; i++)
        if (border[(direction + pDir + 2)%4][i] != p1.border[((pDir + p1.direction)) %4][2 - i])
            return false;

    return true;
    
}

int CarcPiece::getEarnedValue(Piece &p, int pDir) 
{
    //! SUREMENT INUTILE : OK
    CarcPiece &p1 = (CarcPiece &)p;
    int col = 0;
    col = border[(direction + pDir + 2)%4][1];
    p1.color_dir[pDir] = col;
    this->color_dir[(pDir + 2)%4] = col;
    return 0;
}

void CarcPiece::getConnectColor(int *t) const
{
    //! CHANGE POUR METTRE LES COULEUR
    // for(int i = 0; i < 4; i++)
    // {
    //     t[i] = color_dir[i];   
    // }

    for(int i = 0; i < 4; i++)
    {
        t[i] = border[i][1];
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

bool CarcPiece::playOnPiece(int dir, int player)
{
    if(dir >= 0 && dir <= 4 && play[4] == -1) 
    {
        play[dir] = player;
        return true;
    }
    if(dir == 5 && play_center == -1)
    {
        play_center = player;
        return true;
    }
}

void CarcPiece::getPlayPawn(int *t) const
{
    for(int i = 0; i < 4; i++)
    {
        t[i] = play[i];
    }
    t[4] = play_center;
}

int CarcPiece::getCenter() const
{
    return center;
}