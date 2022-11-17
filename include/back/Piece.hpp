#ifndef PIECE_H
#define PIECE_H

#include <ostream>

// Useless ??
enum class Direction
{
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

// Abstract class
class Piece
{
protected:
    int direction;
    int color;

public:
    virtual ~Piece();

    void rotate(bool clockwise);
    virtual int connectable(Piece &p, int pDir) = 0;
    virtual int getEarnedValue(Piece &p, int pDir) = 0;
    virtual std::string toString() const = 0;

    int getDirection() const;
    int getColor() const;

    friend std::ostream &operator<<(std::ostream &out, const Piece &p);
};

#endif