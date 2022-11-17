#ifndef DOMPIECE_H
#define DOMPIECE_H

// For rand() method
#include <cstdlib>

// For building string to print
#include <string>

#include "Piece.hpp"

class DomPiece : public Piece
{
private:
    // DomPieces have constant length : 4 sides with 3 values on each side.
    int tab[4][3];

public:
    DomPiece();
    virtual ~DomPiece();
    int connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;
    std::string toString() const override;
};
#endif