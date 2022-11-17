#ifndef FIRSTSCENE_H
#define FIRSTSCENE_H

#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Scene.hpp"

#include <iostream>

class FirstScene : public Scene
{
private:
    // Current window (needed to draw and to change scene)
    Menu &menu;

    // Font of the text
    sf::Font font;

    // Vector of string that store all the texts.
    std::vector<std::string> options;

    // Vector of texts
    std::vector<sf::Text> texts;

    // Position of the mouse on the screen
    sf::Vector2i pos_mouse;

    // Coordinates of the mouse in the window
    sf::Vector2f mouse_coord;

    // if disappearing
    bool disp;

    // if appearing
    bool app;

    // count frame % 60
    int frame;

    void init();

public:
    FirstScene(Menu &m);
    virtual ~FirstScene();
    void loop_event();
    void render();

    void dispose();
    void display();
};

#endif