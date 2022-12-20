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
        void addPlayer(std::string);

        bool canPlace(int i, int j, Piece &p) override;
        void place(int i, int j, Piece &p) override;

        int search(int i, int j, int di, int dj, CarcType type, bool placing);
        int search_abbaye(int i, int j);

        virtual bool gameOver() override;
};

#endif