#ifndef TRAXPIECE_H
#define TRAXPIECE_H

#include <ostream>

#include "Piece.hpp"

class TraxPiece : public Piece
{
private:
    // TraxPieces only need 2 boolean values to describe the pattern and the color (black/white)
    bool tab[4];
    bool isRecto;

public:
    TraxPiece();
    virtual ~TraxPiece();

    int connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;

    void flip();

    friend std::ostream &operator<<(std::ostream &out, const TraxPiece &p);
};

#endif