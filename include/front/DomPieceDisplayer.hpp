#ifndef DOMPIECEDISPLAYER_H
#define DOMPIECEDISPLAYER_H

#include <vector>

#include "PieceDisplayer.hpp"
#include "back/DomPiece.hpp"

class DomPieceDisplayer : public PieceDisplayer
{
private:
    DomPiece &piece;

    sf::RectangleShape rect;
    sf::Text text;

    void drawRect(int scl);

public:
    DomPieceDisplayer(App &app, int x, int y, DomPiece &p);
    virtual ~DomPieceDisplayer();

    void rotate(bool clockwise) override;

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
    void render(float x, float y, int scl) override;
};
#endif