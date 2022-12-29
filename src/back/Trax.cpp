#include "back/Trax.hpp"

using namespace std;

Trax::Trax() : index_min_i{0}, index_max_i{0}, index_min_j{0}, index_max_j{0}, last_i{0}, last_j{0}, mini{0}, maxi{0}, minj{0}, maxj{0}, moveForced{}, last_player{0}, winner{-1}
{
    s.fill(8*8, 1, 0);
}

Trax::~Trax()
{}

bool Trax::canPlace(int i, int j, Piece &p)
{
    if(!Game::canPlace(i, j, p)) return false;
    if(i > index_max_i && i - index_min_i >= 8) return false;
    if(j > index_max_j && j - index_min_j >= 8) return false;
    if(i < index_min_i && index_max_i - i >= 8) return false;
    if(j < index_min_j && index_max_j - j >= 8) return false;

    if(moveForced.size() != 0)
    {
        for(Pos p : moveForced)
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
        last_player = current_player;
        Game::place(i, j, p);
        last_i = i;
        last_j = j;
        if(i < index_min_i) index_min_i = i;
        if(j < index_min_j) index_min_j = j;
        if(i > index_max_i) index_max_i = i;
        if(j > index_max_j) index_max_j = j;

        getForcedMove(i, j);

        if(moveForced.size() != 0)
        {
            int index = -1;
            for(size_t k = 0; k < moveForced.size(); k++)
            {
                Pos pai = moveForced[k];
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

    TraxPiece *t = (TraxPiece *)p;
    TraxPiece *t2 = (TraxPiece *)board[last_i][last_j];
    if(maxi - mini >= 7) 
    {
        if(t->getType(UP) == color && board[i - 1][j] == nullptr && t2->getType(DOWN) == color && board[last_i + 1][last_j] == nullptr) return true;
        if(t->getType(DOWN) == color && board[i + 1][j] == nullptr && t2->getType(UP) == color && board[last_i - 1][last_j] == nullptr) return true;
    }
    if(maxj - minj >= 7)
    {
        if(t->getType(LEFT) == color && board[i][j - 1] == nullptr && t2->getType(RIGHT) == color && board[last_i][last_j + 1] == nullptr) return true;
        if(t->getType(RIGHT) == color && board[i][j + 1] == nullptr && t2->getType(LEFT) == color && board[last_i][last_j - 1] == nullptr) return true;
    }

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

Player *Trax::getWinner() const
{
    return players[winner];
}

bool Trax::gameOver()
{
    bool rep = false;

    if (DFS(0)) {
         winner = 0;
         rep = true;
    }

    if (DFS(1)) {
        winner = 1;
        rep = true;
    }

    cleanColor();
    return rep;
}

std::vector<Pos> Trax::getMoveForced()
{
    return moveForced;
}
