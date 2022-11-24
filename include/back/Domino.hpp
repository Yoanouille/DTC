#ifndef DOMINO_HPP
#define DOMINO_HPP

#include "Game.hpp"

class Domino : public Game
{
    private:


    public:
        Domino();
        ~Domino();

        bool gameOver();
};

#endif