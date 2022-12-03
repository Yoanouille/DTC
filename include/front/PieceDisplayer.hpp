#ifndef PIECEDISPLAYER_H
#define PIECEDISPLAYER_H

#include <SFML/Graphics.hpp>

#include "back/Piece.hpp"
#include "App.hpp"

class PieceDisplayer : public sf::RectangleShape
{
protected:
    App &app;
    
    // Coordinates on a Board
    sf::Vector2i coordinates;

public:
    PieceDisplayer(App& app, int x, int y);
    virtual ~PieceDisplayer();

    // The Piece inherts rotation() from Shape
    virtual void rotate(bool clockwise) = 0;

    virtual void loop_event() = 0;

    // Abstract method that will be overriden.
    virtual void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) = 0;
};
#endif