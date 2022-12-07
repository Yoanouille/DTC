#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include "back/Game.hpp"
#include <iostream>
#include <vector>

class Carcassonne : public Game
{
    private:
        //vector d'entier pour le nombre de pions de chaque joueur

    public:
        Carcassonne();
        ~Carcassonne();
        void place(int i, int j, Piece &p) override;

        virtual bool gameOver() override;
};

#endif