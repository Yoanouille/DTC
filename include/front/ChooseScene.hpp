#ifndef CHOOSESCENE_HPP
#define CHOOSESCENE_HPP

#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "Scene.hpp"
#include "Button.hpp"

#include <iostream>

class ChooseScene : public Scene
{
private:
    App & app;
    std::vector<Button> options;

    // if disappearing
    bool disp;

    // if appearing
    bool appear;

    sf::Vector2f mousepos;

    vector<std::string> *names;

    int gamemode;

    void init();

    void sit1();
    void sit2();
    void sit3();

public:
    ChooseScene(App &app);
    ~ChooseScene();

    void loop_event();
    void render();

    void dispose();
    void display();
};

#endif