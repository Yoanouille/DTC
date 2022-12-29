#include "back/Trax.hpp"

using namespace std;

/**
 * Constructor
*/
Trax::Trax() : index_min_i{0}, index_max_i{0}, index_min_j{0}, index_max_j{0}, last_i{0}, last_j{0}, mini{0}, maxi{0}, minj{0}, maxj{0}, moveForced{}, last_player{0}, winner{-1}
{
    s.fill(8*8, 1, 0);
}

/**
 * Destructor
*/
Trax::~Trax()
{}

/**
 * redefined the canPlace of Game
*/
bool Trax::canPlace(int i, int j, Piece &p)
{
    //test connexity
    if(!Game::canPlace(i, j, p)) return false;
    
    //test if we are in the grid of 8*8
    if(i > index_max_i && i - index_min_i >= 8) return false;
    if(j > index_max_j && j - index_min_j >= 8) return false;
    if(i < index_min_i && index_max_i - i >= 8) return false;
    if(j < index_min_j && index_max_j - j >= 8) return false;

    //if we have force move, we have to play it
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
        //update variables
        last_player = current_player;
        Game::place(i, j, p);
        last_i = i;
        last_j = j;
        if(i < index_min_i) index_min_i = i;
        if(j < index_min_j) index_min_j = j;
        if(i > index_max_i) index_max_i = i;
        if(j > index_max_j) index_max_j = j;

        //get forced move
        getForcedMove(i, j);

        //if we play a forced move, we need to delete it
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

        //if there is no more move forced, we pass to the next player
        if(moveForced.size() == 0)
        {
            current_player = (current_player + 1)% nb_player;
        }
    }
}

/**
 * get forced move, and store it in moveForced
 * @param i line
 * @param j column
*/
void Trax::getForcedMove(int i, int j)
{
    if(board[i - 1][j] == nullptr && TraxPiece::forcedMove(getNeighbours(i - 1, j)))
        moveForced.push_back({i-1,j});
    if(board[i + 1][j] == nullptr && TraxPiece::forcedMove(getNeighbours(i + 1, j)))
        moveForced.push_back({i+1,j});
    if(board[i][j - 1] == nullptr && TraxPiece::forcedMove(getNeighbours(i, j - 1)))
        moveForced.push_back({i,j-1});
    if(board[i][j + 1] == nullptr && TraxPiece::forcedMove(getNeighbours(i, j + 1)))
        moveForced.push_back({i,j+1});

}


/**
 * @param i column
 * @param j column
 * @return neighbours
*/
vector<TraxPiece *> Trax::getNeighbours(int i, int j)
{
    vector<TraxPiece *> v;
    v.push_back((TraxPiece *)board[i - 1][j]); //UP
    v.push_back((TraxPiece *)board[i][j - 1]); //LEFT
    v.push_back((TraxPiece *)board[i + 1][j]); //DOWN
    v.push_back((TraxPiece *)board[i][j + 1]); //RIGHT

    return v;
}

/**
 * Explore with a color
 * @param i line
 * @param j column
 * @param color color of the search
 * @param pre parent of the recursive call
 * @return if there is a loop, or a line that pass through the board of size 8
*/
bool Trax::explore(int i, int j, int color, Piece *pre)
{
    Piece *p = board[i][j];
    //update variables
    if(i < mini) mini = i;
    if(i > maxi) maxi = i;
    if(j < minj) minj = j;
    if(j > maxj) maxj = j;

    TraxPiece *t = (TraxPiece *)p;
    TraxPiece *t2 = (TraxPiece *)board[last_i][last_j];
    
    // if there is a line that pass through the board of size 8, return true
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

    //color the piece, and get the next the pieces
    p->setColor(1);
    int col[4];
    p->getConnectColor(col);

    bool rep = false;

    //test for each direction if we can explore
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

/**
 * @param color
 * @return if a search with the color, color is finished
*/
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
