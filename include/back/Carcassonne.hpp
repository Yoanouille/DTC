#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include "back/Game.hpp"
#include <iostream>
#include <vector>

typedef struct Triple
{
    int i;
    int j;
    Direction d;
} Triple;

class Carcassonne : public Game
{
    private:
        //vector d'entier pour le nombre de pions de chaque joueur

    public:
        Carcassonne();
        ~Carcassonne();
        void place(int i, int j, Piece &p) override;

        void searchRoad(int i, int j, Direction d);

        virtual bool gameOver() override;
};

#endif