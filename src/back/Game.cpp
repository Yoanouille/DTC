#include "back/Game.hpp"

Game::Game() : plateau{}, players{}, s{}, nb_player{0}, current_player{0}, nb_piece{0}
{}

Game::~Game()
{
    for(Player *p : players)
        delete(p);
}

void Game::add_player(std::string name)
{
    players.push_back(new Player{name});
    nb_player++;
}

Piece &Game::draw()
{
    return *(s.draw());
}

void Game::cleanColor()
{
    for(int i = plateau.get_min(); i <= plateau.get_max(); i++)
    {
        for(int j = plateau[i].get_min(); j <= plateau[i].get_max(); j++)
        {
            plateau[i][j]->cleanColor();
        }
    }
}

bool Game::canPlace(int i, int j, Piece &p)
{
    if(nb_piece == 0) return 0;
    Piece *ph = plateau[i - 1][j];
    Piece *pb = plateau[i + 1][j];
    Piece *pg = plateau[i][j - 1];
    Piece *pd = plateau[i][j + 1];

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

void Game::place(int i, int j, Piece &p)
{
    if(!canPlace(i, j, p)) return;
    plateau[i][j] = &p;
    nb_piece++;

    int score = 0;

    Piece *ph = plateau[i - 1][j];
    Piece *pb = plateau[i + 1][j];
    Piece *pg = plateau[i][j - 1];
    Piece *pd = plateau[i][j + 1];

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

    players[i]->addScore(score);
    //current_player = (current_player + 1) % nb_player;

}