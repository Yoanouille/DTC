#include "back/Domino.hpp"

using namespace std;

/** Constructor */
Domino::Domino(int size = 5) { s.fill(size, 0, 0); }

/** Destructor */
Domino::~Domino() {}

/** Overriden function */
void Domino::place(int i, int j, Piece &p)
{
    Game::place(i, j, p);
    current_player = (current_player + 1) % nb_player;
}

/** Overriden function */
bool Domino::gameOver()
{
    if(s.isEmpty()) cout << "END OF THE GAME!" << endl;
    return s.isEmpty();
}