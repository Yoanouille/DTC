#ifndef DOMPIECE_H
#define DOMPIECE_H

#include "Piece.hpp"

// For rand() method
#include <cstdlib>

// Seems better than usual array
// https://stackoverflow.com/questions/30263303/stdarray-vs-array-performance
#include <array>

class DomPiece : protected Piece
{
private:
    std::array<std::array<int, 3>, 4> tab;

public:
    DomPiece();
    int connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;
};
#endif