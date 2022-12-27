#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include "back/Game.hpp"
#include <iostream>
#include <vector>

class Carcassonne : public Game
{
    private:
        //vector d'entier pour le nombre de pions de chaque joueur seulement pour le comptage final des Fields
        std::vector<int> pawn_player;

    public:
        Carcassonne(int size, int perm);
        ~Carcassonne();
        void addPlayer(std::string name);

        bool canPlace(int i, int j, Piece &p) override;
        void place(int i, int j, Piece &p) override;

        bool canPlacePawn(int i, int j, int di, int dj, Piece &p);
        
        int search(int i, int j, int di, int dj, CarcType type, bool placing, bool final, bool finalField, bool remove);
        void searchAbbaye(int i, int j);

        void searchFinalTownAndRoadAndAbbaye();
        void finalSearchAbbaye(int i, int j);
        void finalSearchField();
        void cleanField();

        virtual bool gameOver() override;
};

#endif