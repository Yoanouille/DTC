#ifndef CARCPIECE_HPP
#define CARCPIECE_HPP

#include "Piece.hpp"
#include <iostream>
#include <vector>

enum CarcType
{
    None = -1,
    Field = 0,
    Town = 1,
    DownTown = 2,
    Road = 3,
    Abbaye = 4,
    Crossroad = 5
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
        int center;

        int pawn[4][3];
        int pawn_center;

        int color_border[4][3];
        int color_center;
        bool bonus;
    
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


        int getColor(int i, int j, bool center) const;
        int getType(int i, int j, bool center) const;
        bool getBonus() const;
        int getNbPawn(int *t, int nb_player);
        bool hasPawn();
        void putPawn(int i, int j, bool center, int player);

        void cleanColor();
        void removeAllPawn();
        void explore(int i, int j, bool cent, CarcType t);
        std::vector<Pos> getNextDir();


};

#endif