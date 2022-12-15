#ifndef CARCPIECE_DISPLAYER_H
#define CARCPIECE_DISPLAYER_H

#include <SFML/Graphics.hpp> 

#include "PieceDisplayer.hpp"
#include "back/CarcPiece.hpp"

class CarcPieceDisplayer : public PieceDisplayer
{
    private:
        CarcPiece &piece;

        int dx;
        int dy;

    public: 
        CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p);
        virtual ~CarcPieceDisplayer();

        void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
        void render(float x, float y, int scl) override;
        Piece &getPiece() override;

        void rotates(bool clockwise) override;
};
#endif