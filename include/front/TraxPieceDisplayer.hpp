#ifndef TRAXPIECEDISPLAYER_H
#define TRAXPIECEDISPLAYER_H

#include "back/TraxPiece.hpp"
#include "AssetsLoader.hpp"
#include "PieceDisplayer.hpp"
#include "Controller.hpp"

class TraxPieceDisplayer : public PieceDisplayer
{
private:
    TraxPiece &piece;

    int dx;
    int dy;

    void setShownSide(bool recto);

public:
    TraxPieceDisplayer(App& app, int x, int y, TraxPiece &p);
    virtual ~TraxPieceDisplayer();

    void flip();
    void rotates(bool clockwise) override;

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse) override;
    void render(float x, float y, int scl) override;
    Piece &getPiece() override;

};

#endif