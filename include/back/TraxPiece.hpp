#ifndef TRAXPIECE_H
#define TRAXPIECE_H

#include <iostream>
#include <string>
#include <vector>

#include "Piece.hpp"

class TraxPiece : public Piece
{
private:
    // TraxPieces only need 2 boolean values to describe the pattern and the color (black/white)
    bool tab[4];
    bool recto;

    int color_dir[4];

public:
    TraxPiece();
    virtual ~TraxPiece();

    bool isRecto() const;
    bool connectable(Piece &p, int pDir) override;
    int getEarnedValue(Piece &p, int pDir) override;
    std::string toString() const override;

    void getConnectColor(int *t) const override;
    static bool forcedMove(std::vector<TraxPiece *> tabp);

    void flip();
};

#endif