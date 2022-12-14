#ifndef DRAWZONE_H
#define DRAWZONE_H

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Button.hpp"
#include "PieceDisplayer.hpp"

class DrawZone {
    private:
        App &app;

        bool isTraxGame;

        sf::RectangleShape container;
        Button sack;

        sf::RectangleShape r;
        PieceDisplayer *pieceViewer;
        Button rotateLeft;
        Button rotateRight;
        Button flipButton;

    public: 
        DrawZone(App &app, bool isTraxGame);
        virtual ~DrawZone();

        App &getApp();
        PieceDisplayer *getPieceViewer();

        void draw();

        PieceDisplayer *pick();

        void render();

    friend class MainScene;
};
#endif