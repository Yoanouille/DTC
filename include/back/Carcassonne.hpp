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

typedef struct Container
{
    int i;
    int j;
    bool pawn[4];
} Container;

class Carcassonne : public Game
{
    private:
        //vector d'entier pour le nombre de pions de chaque joueur

    public:
        Carcassonne();
        ~Carcassonne();
        void place(int i, int j, Piece &p) override;

        int search(int i, int j, Direction d, CarcType type, bool placing);

        virtual bool gameOver() override;
};

#endif