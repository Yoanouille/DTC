#ifndef TRAX_HPP
#define TRAX_HPP

#include "back/Game.hpp"
#include <iostream>
#include <vector>

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

        bool explore(int i, int j, int col, Piece *pre);

        //MANQUE COUP FORCE
        //FAIRE UNE LISTE DE POSITION
        //AJOUTER QUAND QUELQUN POSE LES POSITION P VIDE PARMI CELLE AUTOUR DE LA PIECE POSE TQ:
        // AUTOUR DE P : AU MOINS 2 PIECE POSE ET 2 FOIS MEME COULEUR
        //QUESTION COMMENT DANS LA ROUTINE DE JEU FORCE CES COUPS !
        //LE JOUEUR DOIT LES POSE LUI MEME OU LE JEU LE FAIT A SA PLACE (perso prefere le joueur)
        

    public:
        Trax();
        ~Trax();

        bool DFS(int color);

        bool canPlace(int i, int j, Piece &p) override;
        void place(int i, int j, Piece &p) override;

        virtual bool gameOver();

};

#endif