#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "App.hpp"
#include "Scene.hpp"
#include "ScoreBoard.hpp"
#include "DrawZone.hpp"
#include "TextField.hpp"
#include "PieceDisplayer.hpp"
#include "Pos.hpp"

#include "back/Game.hpp"

class MainScene : public Scene
{
private:
    App &app;

    // Scoreboard
    ScoreBoard scoreBoard;

    // Draw Zone
    DrawZone drawZone;

    // Board of the game
    sf::RectangleShape board;

    // Scale, size of the square on the board
    int scl;

    // offset
    sf::Vector2f off;

    // rectangle to draw different things
    sf::RectangleShape rect;

    sf::RectangleShape rectBG;

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

    int frame;

    PieceDisplayer *current_piece;

    void init();

    void setup_rect(sf::RectangleShape &r, float x, float y);
    void redrawBG();
    void drawRectAndPlay();
    void place();
    void drawMoveForced(std::vector<Pos> &v);
    void moveBoard();

    void initBoard();

public:
    MainScene(App &app, int gamemode, std::vector<std::string> &names);
    virtual ~MainScene();

    void loop_event();
    void render();

    void dispose();
    void display();

friend class ScoreBoard;
};

#endif