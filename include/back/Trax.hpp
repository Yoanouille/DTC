#ifndef TRAX_HPP
#define TRAX_HPP

#include "back/Game.hpp"
#include "TraxPiece.hpp"
#include <vector>
#include <stack>
#include "Pos.hpp"
#include <iostream>

class Trax : public Game
{
    private:
        int index_min_i;
        int index_max_i;

        int index_min_j;
        int index_max_j;

        int last_i;
        int last_j;

        int mini;
        int maxi;
        int minj;
        int maxj;

        std::vector<Pos> moveForced;

        int last_player;

        int winner;

        bool explore(int i, int j, int col, Piece *pre);
        
        std::vector<TraxPiece *> getNeighboors(int i, int j);
        void getForcedMove(int i, int j);

    public:
        Trax();
        ~Trax();

        bool DFS(int color);

        bool canPlace(int i, int j, Piece &p) override;
        void place(int i, int j, Piece &p) override;

        std::vector<Pos> getMoveForced();

        Player *getWinner() const;
        virtual bool gameOver();
};

#endif