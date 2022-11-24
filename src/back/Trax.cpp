#include "back/Trax.hpp"
#include "back/TraxPiece.hpp"

Trax::Trax() 
{
    s.fill(8*8, 1);
}

Trax::~Trax()
{}

bool Trax::gameOver()
{
    return false; //TODO: A Changer EVIDEMENT
}