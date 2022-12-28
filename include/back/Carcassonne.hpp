#ifndef CARCASSONNE_HPP
#define CARCASSONNE_HPP

#include "Game.hpp"
#include "CarcPiece.hpp"
#include "back/PlayerCarc.hpp"
#include <vector>
#include <stack>

class Carcassonne : public Game
{
    private:
        // Vector that stores each player's nb of pawns for the end of the game (point counting for fields)
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