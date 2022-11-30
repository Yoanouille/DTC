#ifndef DOMPIECEDISPLAYER_H
#define DOMPIECEDISPLAYER_H

#include <vector>

#include "PieceDisplayer.hpp"
#include "back/DomPiece.hpp"

class DomPieceDisplayer : public PieceDisplayer
{
private:

public:
    DomPieceDisplayer(App &app, int x, int y, DomPiece &p);
    virtual ~DomPieceDisplayer();

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
    void loop_event() override;
};
#endif