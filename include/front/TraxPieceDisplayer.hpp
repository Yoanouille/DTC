#ifndef TRAXPIECEDISPLAYER_H
#define TRAXPIECEDISPLAYER_H

#include "back/TraxPiece.hpp"
#include "PieceDisplayer.hpp"

class TraxPieceDisplayer : public PieceDisplayer
{
private:
    TraxPiece *piece;

    sf::Texture image;
    sf::Sprite sprite;

public:
    TraxPieceDisplayer(Menu &m, int x, int y);
    virtual ~TraxPieceDisplayer();

    // The Piece inherts rotate() from Shape
    void loop_event();

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl);
};

#endif