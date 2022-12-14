#include "back/Domino.hpp"
#include <iostream>

using namespace std;

Domino::Domino() 
{
    s.fill(20, 0);
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
    if(s.isEmpty()) cout << "FIN DE DOMINO !" << endl;
    return s.isEmpty();
}