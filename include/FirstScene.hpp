#ifndef FIRSTSCENE_HPP
#define FIRSTSCENE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "Scene.hpp"


class FirstScene : public Scene
{
    private:
        Menu &menu;

        sf::Font font;

        std::vector<std::string> options;
        std::vector<sf::Text> texts;

        sf::Vector2i pos_mouse;
        sf::Vector2f mouse_coord;

        void init();

    public:
        FirstScene(Menu &m);
        virtual ~FirstScene();
        void loop_event();
        void render();

};

#endif