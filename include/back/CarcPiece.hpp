#ifndef CARCPIECE_HPP
#define CARCPIECE_HPP

#include "Piece.hpp"

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


};

#endif