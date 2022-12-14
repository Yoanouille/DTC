#ifndef SACK_H
#define SACK_H

#include <algorithm>
#include <random>
#include <exception>
#include <vector>
#include <ostream>

#include "Piece.hpp"
#include "DomPiece.hpp"
#include "TraxPiece.hpp"
#include "CarcPiece.hpp"
#include "UnknownGamemodeException.hpp"

class Sack
{
private:
    int index;
    int size;
    std::vector<Piece *> sack;

    // Used in Carcassonne that uses specific piece.
    void shuffle();

    // Initializes the Sacks depending on the gamemode.
    void initDom(int s);
    void initTrax();
    void initCarcassonne();

public:
    Sack();
    virtual ~Sack();

    void fill(int size, int gamemode);
    bool isEmpty();

    Piece *draw();

    friend std::ostream &operator<<(std::ostream &out, const Sack &s);
};

#endif