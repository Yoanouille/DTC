#include "back/Trax.hpp"
#include "back/TraxPiece.hpp"
#include <stack>
#include <iostream>

using namespace std;

Trax::Trax() : index_min_i{0}, index_max_i{0}, index_min_j{0}, index_max_j{0}, last_i{0}, last_j{0}, mini{0}, maxi{0}, minj{0}, maxj{0}, moveForced{}
{
    s.fill(8*8, 1);
}

Trax::~Trax()
{}

bool Trax::canPlace(int i, int j, Piece &p)
{
    if(!Game::canPlace(i, j, p)) return false;
    if(i > index_max_i && i - index_min_i > 8) return false;
    if(j > index_max_j && j - index_min_j > 8) return false;
    if(i < index_min_i && index_max_i - i > 8) return false;
    if(j < index_min_j && index_max_j - j > 8) return false;

    if(moveForced.size() != 0)
    {
        for(Pair p : moveForced)
        {
            if(p.i == i && p.j == j) return true;
        }
        return false;
    }

    return true;
}


void Trax::place(int i, int j, Piece &p)
{
    if(canPlace(i, j, p))
    {
        Game::place(i, j, p);
        last_i = i;
        last_j = j;

        getForcedMove(i, j);

        if(moveForced.size() != 0)
        {
            int index = -1;
            for(size_t k = 0; k < moveForced.size(); k++)
            {
                Pair pai = moveForced[k];
                if(pai.i == i && pai.j == j) index = k;
            }
            if(index != -1) moveForced.erase(moveForced.begin() + index);
        }
        if(moveForced.size() == 0)
        {
            current_player = (current_player + 1)% nb_player;
        }
    }
}

void Trax::getForcedMove(int i, int j)
{
    if(board[i - 1][j] == nullptr && TraxPiece::forcedMove(getNeighboors(i - 1, j)))
        moveForced.push_back({i-1,j});
    if(board[i + 1][j] == nullptr && TraxPiece::forcedMove(getNeighboors(i + 1, j)))
        moveForced.push_back({i+1,j});
    if(board[i][j - 1] == nullptr && TraxPiece::forcedMove(getNeighboors(i, j - 1)))
        moveForced.push_back({i,j-1});
    if(board[i][j + 1] == nullptr && TraxPiece::forcedMove(getNeighboors(i, j + 1)))
        moveForced.push_back({i,j+1});

}


vector<TraxPiece *> Trax::getNeighboors(int i, int j)
{
    vector<TraxPiece *> v;
    v.push_back((TraxPiece *)board[i - 1][j]); //UP
    v.push_back((TraxPiece *)board[i][j - 1]); //LEFT
    v.push_back((TraxPiece *)board[i + 1][j]); //DOWN
    v.push_back((TraxPiece *)board[i][j + 1]); //RIGHT

    return v;
}

bool Trax::explore(int i, int j, int color, Piece *pre)
{
    Piece *p = board[i][j];
    if(i < mini) mini = i;
    if(i > maxi) maxi = i;
    if(j < minj) minj = j;
    if(j > maxj) maxj = j;

    if(maxi - mini >= 7) return true;
    if(maxj - minj >= 7) return true;

    p->setColor(1);
    int col[4];
    p->getConnectColor(col);

    bool rep = false;

    if(col[Direction::UP] == color)
    {
        if((pre != board[i - 1][j]) && (i - 1 == last_i && j == last_j)) return true;
        if(board[i - 1][j] != nullptr && board[i - 1][j]->getColor() == 0)
        {
            rep = explore(i - 1, j, color, p);
        }
    }
    if(rep) return true;

    if(col[Direction::DOWN] == color)
    {
        if((pre != board[i + 1][j]) && (i + 1 == last_i && j == last_j)) return true;
        if(board[i + 1][j] != nullptr && board[i + 1][j]->getColor() == 0)
        {
            rep = explore(i + 1, j, color, p);
        }
    }
    if(rep) return true;

    if(col[Direction::LEFT] == color)
    {
        if((pre != board[i][j - 1]) && (i == last_i && j - 1 == last_j)) return true;
        if(board[i][j - 1] != nullptr && board[i][j - 1]->getColor() == 0)
        {
            rep = explore(i, j - 1, color, p);
        }
    }
    if(rep) return true;

    if(col[Direction::RIGHT] == color)
    {
        if((pre != board[i][j + 1]) && (i == last_i && j + 1 == last_j)) return true;
        if(board[i][j + 1] != nullptr && board[i][j + 1]->getColor() == 0)
        {
            rep = explore(i, j + 1, color, p);
        }
    }
    return rep;
    
}

bool Trax::DFS(int color)
{
    mini = last_i;
    maxi = last_i;
    minj = last_j;
    maxj = last_j;
    cleanColor();

    return explore(last_i, last_j, color, nullptr);

}

bool Trax::gameOver()
{
    if(s.isEmpty()) cout << "TRAX VIDE" << endl;
    bool rep = DFS(0) || DFS(1);
    cleanColor();
    if(rep) cout << "FIN TRAX" << endl;
    return rep;
}