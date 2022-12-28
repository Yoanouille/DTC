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

        // Global container
        sf::RectangleShape container;

        // A button representing the Sack : When clicked draws if the pieceContainer is empty
        Button sack;

        // Piece Viewer
        sf::RectangleShape r;
        PieceDisplayer *pieceViewer;

        // Buttons
        Button rotateLeft;
        Button rotateRight;
        Button flipButton;
        Button passButton;

        bool appear;

    public: 
        DrawZone(App &app, bool isTraxGame);
        virtual ~DrawZone();

        App &getApp();
        PieceDisplayer *getPieceViewer();

        void draw();

        PieceDisplayer *pick();

        void render();

        void display();

    friend class MainScene;
};
#endif