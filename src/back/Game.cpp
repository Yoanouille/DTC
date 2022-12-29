#include "back/Game.hpp"

using namespace std;

/** Constructor */
Game::Game() : board{}, players{}, s{}, nb_player{0}, current_player{0}, nb_piece{0} {}

/** Destructor */
Game::~Game()
{
    for(Player *p : players)
        delete(p);
}

/**
 * Add the player with the given name.
 * @param name The name of the player
 */
void Game::addPlayer(std::string name)
{
    players.push_back(new Player{name});
    nb_player++;
}

/**
 * Pass to the next player
 */
void Game::pass()
{
    current_player ++;
    current_player = current_player % nb_player;
}

/**
 * Draw a piece in the sack.
 * @return The next piece
*/
Piece &Game::draw()
{
    return *(s.draw());
}

/** Getter : The current player */
int Game::getCurrentPlayer() const
{
    return current_player;   
}

/** Getter : The vector containing all players */
const std::vector<Player *> Game::getPlayers() const 
{
    return players;
}


/**
 * Clean color for searching
 */
void Game::cleanColor()
{
    for(int i = board.get_min(); i <= board.get_max(); i++)
    {
        for(int j = board[i].get_min(); j <= board[i].get_max(); j++)
        {
            if(board[i][j] != nullptr)
                board[i][j]->cleanColor();
        }
    }
}


/**
 * Test if the piece p can be place at (i,j) in the board
 * 
 * @param i line of the piece
 * @param j line of the piece
 * @param p piece
 */
bool Game::canPlace(int i, int j, Piece &p)
{
    if(board[i][j] != nullptr) return false;
    if(nb_piece == 0) return true;
    Piece *ph = board[i - 1][j];
    Piece *pb = board[i + 1][j];
    Piece *pg = board[i][j - 1];
    Piece *pd = board[i][j + 1];

    bool flag = false;

    if(ph != nullptr) 
    {
        flag = true;
        if(!p.connectable(*ph, Direction::DOWN)) return false;
    }

    if(pb != nullptr)
    {
        flag = true;
        if(!p.connectable(*pb, Direction::UP)) return false;
    }

    if(pg != nullptr)
    {
        flag = true;
        if(!p.connectable(*pg, Direction::RIGHT)) return false;
    }

    if(pd != nullptr)
    {
        flag = true;
        if(!p.connectable(*pd, Direction::LEFT)) return false;
    }

    return flag;

}

/**
 * Place the piece at (i,j) in the board
 * 
 * @param i line of the piece
 * @param j line of the piece
 * @param p piece
 */
void Game::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;

    board[i][j] = &p;
    nb_piece++;

    int score = 0;

    Piece *ph = board[i - 1][j];
    Piece *pb = board[i + 1][j];
    Piece *pg = board[i][j - 1];
    Piece *pd = board[i][j + 1];

    if(ph != nullptr) 
    {
        score += p.getEarnedValue(*ph, Direction::DOWN);
    }

    if(pb != nullptr)
    {
        score += p.getEarnedValue(*pb, Direction::UP);
    }

    if(pg != nullptr)
    {
        score += p.getEarnedValue(*pg, Direction::RIGHT);
    }

    if(pd != nullptr)
    {
        score += p.getEarnedValue(*pd, Direction::LEFT);
    }

    players[current_player]->addScore(score);
}

/**
 * @return A copy of the board
*/
vector<PiecePos> Game::getAllPiece()
{
    vector<PiecePos> v{};
    for(int i = board.get_min(); i <= board.get_max(); i++)
    {
        for(int j = board[i].get_min(); j <= board.get_max(); j++)
        {
            if(board[i][j] != nullptr)
                v.push_back({board[i][j], i, j});
        }
    }
    return v;
}

/** @return The winner */
Player *Game::getWinner() const
{
    int max = -1;
    Player *win = nullptr;
    for(Player *p : players)
    {
        if(p->getScore() > max)
        {
            max = p->getScore();
            win = p;
        }
    }
    return win;
}