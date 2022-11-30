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

    // The Piece we attache the Displayer to
    Piece &piece;

public:
    PieceDisplayer(Menu &m, int x, int y, Piece &p);
    virtual ~PieceDisplayer();

    void rotate(bool clockwise);

    // The Piece inherts rotation() from Shape
    virtual void loop_event() = 0;

    // Abstract method that will be overriden.
    virtual void render(sf::Vector2f &off, sf::RectangleShape &board, int scl) = 0;
};
#endif