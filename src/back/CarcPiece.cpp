#include "back/CarcPiece.hpp"

#include <iostream>
#include <vector>

using namespace std;

/**
 * Constructor 
 * 
 * All the pieces have to be hardcoded somewhere. We arbitrarilly chose the constructor.
 * We'll follow the order on CPiece.png line by line.
 * 
 * Notice that between 2 and 12 included, pieces with even id have a shields (bonus points).
 * 
 * TODO : Maybe we can factorize the harcoding a little bit but it's not a top priority task.
 * @param id The id
 */
CarcPiece::CarcPiece(int d) : 
    id{d}, 
    pawn{-1}, pawn_coordinates{-1,-1}, 
    color_center{-1}, 
    bonus{d > 1 && d <13 && d%2 == 0}
{
    // Initialize the marking
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            color_border[i][j] = -1;
            color_center_border[i][j] = -1;
        }
    }

    switch(id){
        case(0): 
            for(size_t i = 0; i < 4; i++){
                for(size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }
            center = Abbaye;
            break;
        
        case(1): 
            for (size_t i = 0; i < 4 ; i++){
                for (size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }

            border[2][1] = Road;
            center_border[2][1] = Road;
            center = Abbaye;
            break;

        case(2):
            for (size_t i = 0; i < 4 ; i++){
                for (size_t j = 0; j < 3; j++){
                    border[i][j] = Town;
                    center_border[i][j] = Town;
                }
            }

            center = Town;
            break;

        case(3): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for (size_t i = 0; i < 4 ; i++)
                    center_border[i][j] = Town;
            }


            center = Town;
            break;

        case(4):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for (size_t i = 0; i < 4 ; i++)
                    center_border[i][j] = Town;
            }

            center = Town;
            break;

        case(5): 
           for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for (size_t i = 0; i < 4 ; i++)
                    center_border[i][j] = Town;
            }
            
            border[2][1] = Road;
            center_border[2][1] = Road;
            center = Town;
            break;

        case(6):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for (size_t i = 0; i < 4 ; i++)
                    center_border[i][j] = Town;
            }
            
            border[2][1] = Road;
            center_border[2][1] = Road;
            center = Town;
            break;

        case(7): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Town;
                center_border[1][j] = Town;
                center_border[2][j] = Field;
                center_border[3][j] = Field;
            }

            center = Field;
            break;

        case(8): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Town;
                center_border[1][j] = Town;
                center_border[2][j] = Field;
                center_border[3][j] = Field;
            }
            center = Field;
            break;

        case(9):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Town;
                center_border[1][j] = Town;
                center_border[2][j] = Road;
                center_border[3][j] = Road;
            }
            
            border[2][1] = Road;
            border[3][1] = Road;
            center_border[2][2] = Field;
            center_border[3][0] = Field;
            center = Field;
            break;

        case(10):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Town;
                center_border[1][j] = Town;
                center_border[2][j] = Road;
                center_border[3][j] = Road;
            }
            
            border[2][1] = Road;
            border[3][1] = Road;
            center_border[2][2] = Field;
            center_border[3][0] = Field;
            center = Field;
            break;

        case(11): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Town;
            }

            center = Town;
            break;

        case(12):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Field;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Town;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Town;
            }

            center = Town;
            break;

        case(13): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Town;
                border[2][j] = Field;
                border[3][j] = Field;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Field;
            }

            center = Field;
            break;

        case(14): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Town;
                border[3][j] = Field;

                center_border[0][j] = Town;
                center_border[1][j] = Field;
                center_border[2][j] = Town;
                center_border[3][j] = Field;
            }

            center = Field;
            break;

        case(15): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Field;
            }

            center = Field;
            break;

        case(16): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Field;
                center_border[1][j] = Road;
                center_border[2][j] = Road;
                center_border[3][j] = Field;

            }
            
            border[1][1] = Road;
            border[2][1] = Road;
            center_border[1][3] = Field;
            center_border[2][0] = Field;
            
            center = Field;
            break;

        case(17): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                center_border[0][j] = Field;
                center_border[1][j] = Field;
                center_border[2][j] = Road;
                center_border[3][j] = Road;

            }
            
            border[3][1] = Road;
            border[2][1] = Road;
            center_border[3][0] = Field;
            center_border[2][2] = Field;
            
            center = Field;
            break;

        case(18):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Field;
            }
            
            border[3][1] = Road;
            border[2][1] = Road;
            border[1][1] = Road;
            center_border[3][1] = Road;
            center_border[2][1] = Road;
            center_border[1][1] = Road;
            center = Crossroad;
            break;

        case(19): 
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Field;
            }
            
            border[3][1] = Road;
            border[1][1] = Road;
            center_border[3][1] = Road;
            center_border[1][1] = Road;
            center = Road;
            break;

        case(20):
            for(size_t i = 0; i < 4; i++){
                for(size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }
            
            border[0][1] = Road;
            border[2][1] = Road;
            center_border[0][1] = Road;
            center_border[2][1] = Road;
            center = Road;
            break;

        case(21):
            for(size_t i = 0; i < 4; i++){
                for(size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }
            
            
            border[1][1] = Road;
            border[2][1] = Road;
            center_border[1][1] = Road;
            center_border[1][2] = Road;
            center_border[2][1] = Road;
            center_border[2][2] = Road;
            center = Field;
            break;
            
        case(22):
            for(size_t i = 0; i < 4; i++){
                for(size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }
            
            border[1][1] = Road;
            border[2][1] = Road;
            border[3][1] = Road;
            center_border[1][1] = Road;
            center_border[2][1] = Road;
            center_border[3][1] = Road;
            center = Crossroad;
            break;

        case(23): 
            for(size_t i = 0; i < 4; i++){
                for(size_t j = 0; j < 3; j++){
                    border[i][j] = Field;
                    center_border[i][j] = Field;
                }
            }

            for(size_t i = 0; i < 4; i++){
                border[i][1] = Road;
                center_border[i][1] = Road;
            }

            center = Crossroad;
            break;

        case(24):
            for(size_t j = 0; j < 3; j++){
                border[0][j] = Town;
                border[1][j] = Field;
                border[2][j] = Field;
                border[3][j] = Field;

                for(size_t i = 0; i < 4; i++)
                    center_border[i][j] = Field;
            }
            
            border[3][1] = Road;
            border[1][1] = Road;
            center_border[3][1] = Road;
            center_border[1][1] = Road;
            center = Road;
            break;
    }
}

/** Destructor : Does nothing. */
CarcPiece::~CarcPiece() {}

/** Getter : id*/
const int CarcPiece::getId() const{ return id; }

/** Getter : bonus*/
bool CarcPiece::getBonus() const { return bonus; }

/** Getter : center*/
CarcType CarcPiece::getCenter() const { return center; }

/** 
 * Getter : color of border or center_border [i][j] or color_center.
 * 
 * @param i the border's i-th array
 * @param j The color of the j-th subcase of tje i-th array
 * @param centArray A boolean that is true if we are looking for color_center_border
 * @param cent A boolean that is true if we are looking for color_center
 */
int CarcPiece::getColor(int i, int j, bool centArray, bool cent) const
{
    if(cent) return color_center;
    if(centArray) return color_center_border[(i + direction) % 4][j];
    return color_border[(i + direction) % 4][j];
}

/** 
 * Getter : color of border or center_border [i][j] or color_center.
 * 
 * @param i the border's i-th array
 * @param j The color of the j-th subcase of the i-th array
 * @param centArray A boolean that is true if we are looking for center_border
 * @param cent A boolean that is true if we are looking for center
 */
CarcType CarcPiece::getType(int i, int j, bool centArray, bool cent) const
{
    if(cent) return center;
    if(centArray) return center_border[(i + direction) % 4][j];
    return border[(i + direction) % 4][j];
}

/** Getter : pawn */
int CarcPiece::getPawn() const { return pawn; }

/** Getter : pawn_coordinates */
int * CarcPiece::getPawnCoordinates(){
    return pawn_coordinates;
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
        t[i] = border[(i + direction) % 4][1];
}

string CarcPiece::toString() const
{
//     string s{"  "};
//     for (size_t j = 0; j < 3; j++)
//         s += to_string(border[direction][j]) + " ";
//     s += "\n  ";
//     for (size_t j = 0; j < 3; j++)
//         s += to_string(center_border[direction][j]) + " ";
//     s += "\n";

//     for (size_t j = 0; j < 3; j++){
//         s += to_string(border[(direction + 1) % 4][2 - j]) + to_string(center_border[(direction + 1) % 4][2 - j]) + "  ";
//         s += (j == 1 ? to_string(center) : " ") + "  ";
//         s += to_string(border[(direction + 3) % 4][j]) + to_string(border[(direction + 3) % 4][j]) + "\n";
//     }
//     s += "  ";

//     for (size_t j = 0; j < 3; j++)
//         s += to_string(center_border[(direction + 2) % 4][2 - j]) + " ";
//     s += "\n  ";
//     for (size_t j = 0; j < 3; j++)
//         s += to_string(border[(direction + 2) % 4][2 - j]) + " ";

//   return s;
    return to_string(id) + " ";
}

/**
 * Place a pawn on the Piece.
 * ! Center will have the coordinates (4,j). (j can be random)
 * 
 * @param i The side
 * @param j The index of the element in the i-th array
 * @param player The owner of the pawn
 */
void CarcPiece::placePawn(int i, int j, int player){
    pawn = player;
    pawn_coordinates[0] = i;
    pawn_coordinates[1] = j;
}

/** Remove the pawn on the Piece. */
void CarcPiece::removePawn() {
    pawn = -1;
    pawn_coordinates[0] = -1;
    pawn_coordinates[1] = -1;
}

/** Check if the Piece has a pawn or not. */
bool CarcPiece::hasPawn() { return pawn != -1; }

/**
 * Explore the Piece from a given position and a given CarcType
 * ! It doesn't clean the markings.
 * 
 * Beginning the exploration on center_border is useless so we'll just allow
 * explorations from center and border.
 */
void CarcPiece::beginExplore(int i, int j, bool cent, CarcType t)
{
    if(cent)
        exploreCenter(i,j,cent,t);
    else explore((i + direction) % 4,j,t);
}

/**
 * Exploring method used for connectivity test of a given CarcType.
 * 
 * @param i The side we focus on
 * @param j The index of element of the i-th array
 * @param t The CarcType we are exploring
 */
void CarcPiece::explore(int i, int j, CarcType t)
{
    // If the subcase is already marked then we do nothing.
    if(color_border[i][j] == 1) return;

    // Else we mark it and we explore the center and the neighbours.
    // If the subcase is in a corner, we have to explore its neighbour in the adjacent array.
    color_border[i][j] = 1;
    exploreCenter(i,j,false,t);

    if(j == 1) 
    {
        if(color_border[i][0] == -1 && border[i][0] == t) explore(i, 0, t);
        if(color_border[i][2] == -1 && border[i][2] == t) explore(i, 2, t);
    } 

    else if(j == 0) 
    {
        if(color_border[i][1] == -1 && border[i][1] == t) explore(i, 1, t);
        if(color_border[(i + 1) % 4][2] == -1 && border[(i + 1) % 4][2] == t) explore((i + 1) % 4, 2, t);
    } 

    else 
    {
        if(color_border[i][1] == -1 && border[i][1] == t) explore(i, 1, t);
        if(color_border[(i + 3) % 4][0] == -1 && border[(i + 3) % 4][0] == t) explore((i + 3) % 4, 0, t);
    }
}

/**
 * Exploring method for the center arrays and center.
 * 
 * @param i The index of the center's subarray
 * @param j The index of the element of the i-th array
 * @param cent A boolean that is True when the exploration is on the center
 * @param t The CarcType
 */
void CarcPiece::exploreCenter(int i, int j, bool cent, CarcType t)
{
    // If the subcase is already marked then we do nothing.
    if(color_center_border[i][j] == 1) return;
    
    // If we're exploring the center
    // Mark it and explore all the subcases in the center_border that has the type t
    if(cent)
    {
        color_center = 1;

        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 3; j++)
                if(color_center_border[i][j] == -1 && border[i][1] == t) exploreCenter(i, 1, false, t);
    } 
    
    // If we are exploring a subcase in the center_border
    // We mark it and we explore its neighbours including
    // the center, the neighbour subcases in center_border AND in border.
    else 
    {
        color_center_border[i][j] = 1;
        if(color_center == -1 && center == t) exploreCenter(0,0,true,t);

        if(j == 1)
        {
            if(color_center_border[i][0] == -1 && center_border[i][0] == t) exploreCenter(i, 0, false, t);
            if(color_center_border[i][2] == -1 && center_border[i][2] == t) exploreCenter(i, 2, false, t);
        } 

        else if(j == 0)
        {
            if(color_center_border[i][1] == -1 && center_border[i][1] == t) exploreCenter(i, 1, false, t);
            if(color_center_border[(i + 1) % 4][2] == -1 && center_border[(i + 1) % 4][2] == t) exploreCenter((i + 1) % 4, 2, false, t);
        } 
        
        else 
        {
            if(color_center_border[i][1] == -1 && center_border[i][1] == t) exploreCenter(i, 1, false, t);
            if(color_center_border[(i + 3) % 4][0] == -1 && center_border[(i + 3) % 4][0] == t) exploreCenter((i + 3) % 4, 0, false, t);
        }

        explore(i,j,t);
    }
}

/**
 * Reset all the colors for future explorations.
 * ! Should be called after each beginExplore 
 */
void CarcPiece::cleanColor()
{
    color = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            color_border[i][j] = -1;
            color_center_border[i][j] = -1;
        }
    }
    color_center = -1;
}

// /** Printing Method for colors */
// void CarcPiece::printColor()
// {
//     string s{" "};
//     for (size_t j = 0; j < 3; j++)
//         s += to_string(color_border[direction][j]) + " ";
//     s += "\n";

//     for (size_t j = 0; j < 3; j++)
//         s += to_string(color_border[(direction + 1) % 4][2 - j]) + "  " + (j == 1 ? to_string(pawn_center) : " ") + "  " + to_string(pawn[(direction + 3) % 4][j]) + "\n";
//     s += " ";
//     for (size_t j = 0; j < 3; j++)
//         s += to_string(color_border[(direction + 2) % 4][2 - j]) + " ";   
//     cout << s << endl; 
// }

vector<Pos> CarcPiece::getNextDir()
{
    vector<Pos> next_dir{};
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 3; j++)
            if(color_border[i][j] != -1) 
                next_dir.push_back({(i - direction + 4) % 4, j});

    return next_dir;
}