#ifndef TRAX_HPP
#define TRAX_HPP

#include "back/Game.hpp"

class Trax : public Game
{
    private:
        int index_min_i;
        int index_max_i;

        int index_min_j;
        int index_max_j;

        int last_i;
        int last_j;

    public:
        Trax();
        ~Trax();

        bool canPlace(int i, int j, Piece &p);

        virtual bool gameOver();

};

#endif