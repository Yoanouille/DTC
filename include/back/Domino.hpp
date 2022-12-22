#ifndef DOMINO_HPP
#define DOMINO_HPP

#include "Game.hpp"

class Domino : public Game
{
    public:
        Domino();
        ~Domino();

        void place(int, int, Piece &p);

        bool gameOver();
};

#endif