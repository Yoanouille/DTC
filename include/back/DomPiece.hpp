#ifndef DOMPIECE_H
#define DOMPIECE_H

// For rand() method
#include <cstdlib>
#include <string>
#include <iostream>

#include "Piece.hpp"

class DomPiece : public Piece
{
private:
    // DomPieces have constant length : 4 sides with 3 values on each side.
    int tab[4][3];

public:
    DomPiece();
    virtual ~DomPiece();

    // Getters
    int getVal(int dir, int i);

    // Overriden methods from Piece
    bool connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;
    std::string toString() const override;
};
#endif