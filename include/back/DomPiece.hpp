#ifndef DOMPIECE_H
#define DOMPIECE_H

// For rand() method
#include <cstdlib>

// Seems better than usual array
// https://stackoverflow.com/questions/30263303/stdarray-vs-array-performance
#include <array>

// For basic tests through printing
#include <ostream>

#include "Piece.hpp"

class DomPiece : public Piece
{
private:
    // DomPieces have constant length : 4 sides with 3 values on each side.
    std::array<std::array<int, 3>, 4> tab;

public:
    DomPiece();
    virtual ~DomPiece();
    int connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;

    friend std::ostream &operator<<(std::ostream &out, const DomPiece &p);
};
#endif