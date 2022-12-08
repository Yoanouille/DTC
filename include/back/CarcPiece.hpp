#ifndef CARCPIECE_HPP
#define CARCPIECE_HPP

#include "Piece.hpp"

enum CarcType
{
    Field = 0,
    Town = 1,
    Road = 2,
    Abbaye = 3,
    Crossroad = 4,
};

class CarcPiece : public Piece
{
    private:
        int const id;

        int border[4][3];
        int center;

        int play[4];
        int play_center;

        int color_dir[4];
    
    public:
        CarcPiece(int id);
        ~CarcPiece();

        bool connectable(Piece &p, int pDir) override;
        int getEarnedValue(Piece &p, int pDir) override;
        std::string toString() const override;
        void getConnectColor(int *t) const override;
        bool playOnPiece(int dir, int player);
        void getPlayPawn(int *t) const;
        int getCenter() const;


};

#endif