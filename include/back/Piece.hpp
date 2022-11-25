#ifndef PIECE_H
#define PIECE_H

#include <ostream>

// Useless ??
enum Direction
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
    Piece();
    virtual ~Piece();

    void rotate(bool clockwise);
    virtual bool connectable(Piece &p, int pDir, int dir) = 0;
    virtual int getEarnedValue(Piece &p, int pDir) = 0;
    virtual std::string toString() const = 0;

    int getDirection() const;
    int getColor() const;
    void cleanColor();
    virtual void getConnectColor(int color, int *t);

    friend std::ostream &operator<<(std::ostream &out, const Piece &p);
};

#endif