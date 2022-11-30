#ifndef MainMenu_H
#define MainMenu_H

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Scene.hpp"

#include <iostream>

class MainMenu : public Scene
{
private:
    // Current Window (needed to draw and to change scene)
    App &app;

    // Vector of string that store all the texts.
    std::vector<std::string> options;

    // Vector of texts
    std::vector<sf::Text> texts;

    // Position of the mouse on the screen
    sf::Vector2i pos_mouse;

    // Coordinates of the mouse in the Window
    sf::Vector2f mouse_coord;

    // if disappearing
    bool disp;

    // if appearing
    bool appear;

    int speed;

    void init();

public:
    MainMenu(App &app);
    ~MainMenu();

    void loop_event();
    void render();

    void dispose();
    void display();
};

#endif