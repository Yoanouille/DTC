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
        void addPlayer(std::string name);

        void place(int i, int j, Piece &p) override;

        bool canPlacePawn(int i, int j, int di, int dj);
        void placePawn(int i, int j, int di, int dj, int player);

        int search(int i, int j, int di, int dj, CarcType type, bool placing);
        void searchAbbaye(int i, int j);

        virtual bool gameOver() override;
};

#endif