#ifndef TRAXPIECEDISPLAYER_H
#define TRAXPIECEDISPLAYER_H

#include "back/TraxPiece.hpp"
#include "PieceDisplayer.hpp"
#include "Controller.hpp"

class TraxPieceDisplayer : public PieceDisplayer
{
private:
    TraxPiece &piece;
    // Static textures that will be loaded once and for all
    // (It is recommended to use the least number of texture)
    static sf::Texture textureRecto;
    static sf::Texture textureVerso;

    void setShownSide(bool recto);

public:
    // Loading method
    static void loadTextures();

    TraxPieceDisplayer(Menu &m, TraxPiece &p, int x, int y);
    virtual ~TraxPieceDisplayer();

    void flip();

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
    
    // The Piece inherts rotate() from Shape
    void loop_event() override;
};

#endif