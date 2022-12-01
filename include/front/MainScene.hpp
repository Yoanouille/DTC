#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Scene.hpp"
#include "front/PieceDisplayer.hpp"
#include "back/Game.hpp"

#include <iostream>
#include <vector>

class MainScene : public Scene
{
private:
    // current window (needed to draw and to change scene)
    App &app;

    // White rectangle (future scoreboard)
    sf::RectangleShape scoreBoard;

    // Board of the game
    sf::RectangleShape board;

    // Scale, size of the square on the board
    int scl;

    // offset
    sf::Vector2f off;

    // rectangle to draw different things
    sf::RectangleShape rect;

    // position of the mouse on the screen
    sf::Vector2i pos_mouse;

    // coordonne of the mouse in the window
    sf::Vector2f mouse_coord;

    // different pos to draw (actually strore the green square)
    std::vector<PieceDisplayer*> pos;

    // if the right button of the mouse id pressed
    bool right_pressed;

    bool left_pressed;

    // old position of the mouse
    sf::Vector2f old_pos;

    // if disappearing
    bool disp;

    // if appearing
    bool appear;

    int speed1;

    int speed2;

    Game *game;

    void init();

    void setup_rect(sf::RectangleShape &r, float x, float y);

public:
    MainScene(App &app);
    virtual ~MainScene();

    void loop_event();
    void render();

    void dispose();
    void display();
};

#endif