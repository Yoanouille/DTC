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

    void setShownSide(bool recto);

public:
    TraxPieceDisplayer(App &app, int x, int y, TraxPiece &p);
    virtual ~TraxPieceDisplayer();

    void flip();

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
    
    // The Piece inherts rotate() from Shape
    void loop_event() override;

    void rotate(bool clockwise) override;
};

#endif