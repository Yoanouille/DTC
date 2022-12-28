#ifndef PLAYERCARC_HPP
#define PLAYERCARC_HPP

#include "Player.hpp"

/**
 * PlayerCarc is a Player that has pawns in addition.
 */
class PlayerCarc : public Player
{
    private:
        int nb_pawn;
    
    public:
        PlayerCarc(std::string n);
        ~PlayerCarc();
        void addPawn(int nb);
        int getNbPawn() const;
};

#endif