#ifndef CARCPIECE_HPP
#define CARCPIECE_HPP

#include "Piece.hpp"
#include <iostream>
#include <vector>

// ! Ajouter Type Plaine/Route et adapter explore
enum CarcType
{
    Field = 0,
    Town = 1,
    Road = 2,
    Abbaye = 3,
    Crossroad = 4,
};

typedef struct Pos
{
    int i;
    int j;
} Pos;

class CarcPiece : public Piece
{
    private:
        int const id;

        int border[4][3];

        // ! Changer explore et ajouter un explore center
        // int center_border[4][3];
        int center;

        int pawn[4][3];
        int pawn_center;

        int color_border[4][3];
        int color_center;
        bool bonus;

        // Used by beginExplore
        void explore(int i, int j, bool cent, CarcType t);
    
    public:


        CarcPiece(int id);
        ~CarcPiece();

        const int getId() const;

        bool connectable(Piece &p, int pDir) override;
        void getConnectColor(int *t) const override;
        std::string toString() const override;
        bool playOnPiece(int dir, int player);
        void getPlayPawn(int *t) const;
        int getCenter() const;
        void removePawn(int d);


        int getColor(int i, int j, bool cent) const;
        int getType(int i, int j, bool cent) const;
        bool getBonus() const;
        int getNbPawn(int *t, int nb_player);
        bool hasPawn();
        void putPawn(int i, int j, bool cent, int player);
        Pos getPosPawn() const;

        void cleanColor() override;
        void printColor();
        void removeAllPawn();
        void beginExplore(int i, int j, bool cent, CarcType t);
        std::vector<Pos> getNextDir();


};

#endif