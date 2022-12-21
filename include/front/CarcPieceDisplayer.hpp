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

        sf::RectangleShape rect;

        sf::Color *color;

        void drawRect(sf::Vector2f &mouse, int scl);
        void drawPawn(int scl);

    public: 
        CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p);
        virtual ~CarcPieceDisplayer();

        void render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse) override;
        void render(float x, float y, int scl) override;
        Piece &getPiece() override;

        void rotates(bool clockwise) override;

        void nextState() override;
        bool isFinalState() override;

        void handleClick(sf::Vector2f &mouse, Player *p, int player, int scl) override;
        void removeHandle(Player *p, int player) override;
};
#endif