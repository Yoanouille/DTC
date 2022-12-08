#ifndef DRAWZONE_H
#define DRAWZONE_H

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Button.hpp"

class DrawZone {
    private:
        App &app;

        bool isTraxGame;

        sf::RectangleShape container;
        Button sack;

        sf::RectangleShape pieceViewer;
        Button rotateLeft;
        Button rotateRight;
        Button flipButton;

    public: 
        DrawZone(App &app, bool isTraxGame);
        virtual ~DrawZone();

        void render();
};
#endif