#ifndef MainMenu_H
#define MainMenu_H

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Button.hpp"
#include "Scene.hpp"

#include <iostream>

class MainMenu : public Scene
{
private:
    std::vector<Button> options;

    // if disappearing
    bool disp;

    // if appearing
    bool appear;

    int speed;

    void init();

public:
    MainMenu();
    ~MainMenu();

    void loop_event();
    void render();

    void dispose();
    void display();
};

#endif