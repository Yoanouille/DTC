#ifndef TRAXPIECEDISPLAYER_H
#define TRAXPIECEDISPLAYER_H

#include "back/TraxPiece.hpp"
#include "PieceDisplayer.hpp"

class TraxPieceDisplayer : public PieceDisplayer
{
private:
    // Static textures that will be loaded once and for all
    // (It is recommended to use the least number of texture)
    static sf::Texture &textureRecto;
    static sf::Texture &textureVerso;

    // Loading method
    static void loadTextures();

    // The TraxPiece we attach our displayer to
    TraxPiece *piece;

    // Independant displaying of the Texture fir a single Piece.
    sf::Sprite sprite;

public:
    TraxPieceDisplayer(Menu &m, int x, int y);
    virtual ~TraxPieceDisplayer();

    // The Piece inherts rotate() from Shape
    void loop_event() override;

    void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) override;
};

#endif