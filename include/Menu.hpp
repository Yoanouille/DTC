#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include <iostream>
#include <string>

class Menu : public sf::RenderWindow
{
    private:
        int width;
        int height;


        Scene *sc;

        sf::Texture image;
        sf::Sprite bg;


        void init();
        void loop_event();
        void render();
    
    public:
        Menu();
        virtual ~Menu();
        void run_menu();

        int get_height() const;
        int get_width() const;

};

#endif