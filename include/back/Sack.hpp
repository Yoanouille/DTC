#ifndef SACK_H
#define SACK_H

#include <exception>
#include <vector>
#include <ostream>

#include "Piece.hpp"
#include "DomPiece.hpp"
#include "TraxPiece.hpp"

class Sack
{
private:
    int index;
    int size;
    std::vector<Piece *> sack;

    // Used in Carcassonne that uses specific piece.
    void shuffle();

    // Initializes the Sacks depending on the gamemode.
    void initDom();
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

// Exception used in Sack's constructor
class UnknownGamemodeException : public std::exception
{
    const char *what() const throw();
};
#endif