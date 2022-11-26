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

    // The Piece we attache the Displayer to
    Piece &piece;

    // Coordinates on a Board
    sf::Vector2i coordinates;

public:
    PieceDisplayer(Menu &m, Piece& p, int x, int y);
    virtual ~PieceDisplayer();

    void rotate(bool clockwise);

    // The Piece inherts rotation() from Shape
    virtual void loop_event() = 0;

    // Abstract method that will be overriden.
    virtual void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) = 0;
};
#endif