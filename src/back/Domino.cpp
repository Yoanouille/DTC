#include "back/Domino.hpp"

Domino::Domino() 
{
    s.fill(0, 20);
}

Domino::~Domino()
{

}

bool Domino::gameOver()
{
    return s.isEmpty();
}