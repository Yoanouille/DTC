#ifndef PIECEDISPLAYER_H
#define PIECEDISPLAYER_H

#include <SFML/Graphics.hpp>

#include "back/Piece.hpp"
#include "Menu.hpp"

class PieceDisplayer : public sf::RectangleShape
{
protected:
    // Application's window that catch the events
    Menu &menu;

    // Coordinates on a Board
    sf::Vector2i coordinates;

public:
    PieceDisplayer(Menu &m);
    virtual ~PieceDisplayer();

    // The Piece inherts SetRotation() from Shape
    void loop_event();

    // Abstract method that will be overriden.
    virtual void render() = 0;
};
#endif