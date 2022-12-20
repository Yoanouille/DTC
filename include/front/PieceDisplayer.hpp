#ifndef PIECEDISPLAYER_H
#define PIECEDISPLAYER_H

#include <SFML/Graphics.hpp>

#include "back/Piece.hpp"
#include "App.hpp"

class PieceDisplayer : public sf::RectangleShape
{
protected:
    App &app;

    int state;
    
    // Coordinates on a Board
    sf::Vector2i coordinates;

public:
    PieceDisplayer(App& app, int x, int y);
    virtual ~PieceDisplayer();

    void setPos(int x, int y);

    // The Piece inherts rotate() from Shape
    virtual void rotates(bool clockwise) = 0;

    // Abstract method that will be overriden.
    virtual void render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse) = 0;

    virtual void render(float x, float y, int scl) = 0;

    virtual void nextState();

    virtual bool isFinalState();

    virtual void handleClick(sf::Vector2f &mouse, Player *p, int player, int scl);
    virtual void removeHandle(Player *p, int player);

    int getState() const;
    sf::Vector2i getCoord() const;

    virtual Piece &getPiece() = 0;
};
#endif