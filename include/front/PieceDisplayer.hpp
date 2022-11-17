#ifndef PIECEDISPLAYER_H
#define PIECEDISPLAYER_H

#include <SFML/Graphics.hpp>

#include "back/Piece.hpp"
#include "Menu.hpp"

class PieceDisplayer : public sf::RectangleShape
{
private:
    // The Piece we attach the graphic element.
    Piece &piece;

    // Application's window that catch the events
    Menu &menu;

    // Coordinates on a Board
    sf::Vector2i coordinates;

public:
    virtual ~PieceDisplayer();

    // The Piece inherts SetRotation() from Shape
    void loop_event();

    // Abstract method that will be overriden.
    virtual void render() = 0;
};
#endif