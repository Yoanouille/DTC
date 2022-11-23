#ifndef DOMPIECEDISPLAYER_H
#define DOMPIECEDISPLAYER_H

#include <vector>

#include "PieceDisplayer.hpp"
#include "back/DomPiece.hpp"

class DomPieceDisplayer : public PieceDisplayer
{
private:
    // The Piece we attach the graphic element.
    DomPiece *piece;

public:
    DomPieceDisplayer(Menu &m, DomPiece &p);
    virtual ~DomPieceDisplayer();

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
};
#endif