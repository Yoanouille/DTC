#include "back/Domino.hpp"

Domino::Domino() 
{
    s.fill(0, 20);
}

Domino::~Domino()
{

}

void Domino::place(int i, int j, Piece &p)
{
    Game::place(i, j, p);
    current_player = (current_player + 1) % nb_player;
}

bool Domino::gameOver()
{
    return s.isEmpty();
}