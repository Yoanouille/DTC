#include "back/Trax.hpp"
#include "back/TraxPiece.hpp"

Trax::Trax() : index_min_i{0}, index_max_i{0}, index_min_j{0}, index_max_j{0}
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
    return true;
}

bool Trax::gameOver()
{
    return false; //TODO: A Changer EVIDEMENT
}