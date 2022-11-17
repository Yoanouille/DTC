#ifndef FIRSTSCENE_HPP
#define FIRSTSCENE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Scene.hpp"


class FirstScene : public Scene
{
    private:

        //current window (needed to draw and to change scene)
        Menu &menu;

        //Font of the text
        sf::Font font;

        //vector of string that store the string of the texts
        std::vector<std::string> options;

        //vector of texts
        std::vector<sf::Text> texts;

        //position of the mouse on the screen
        sf::Vector2i pos_mouse;

        //coordonne of the mouse in the window
        sf::Vector2f mouse_coord;

        //if disappearing
        bool disp;

        //if appearing
        bool app;

        //count frame % 60
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