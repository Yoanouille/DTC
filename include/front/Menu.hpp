#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include <iostream>
#include <string>

//Class that represents the window
class Menu : public sf::RenderWindow
{
    private:

        //Dimension
        int width;
        int height;


        //current Scene
        Scene *sc;
        //old current Scene
        Scene *old_sc;

        //image, currently store the background
        sf::Texture image;

        //Sprite of the background, need image
        sf::Sprite bg;

        void init();
        void loop_event();
        void render();
    
    public:
        Menu();
        virtual ~Menu();

        //launch the event loop and the render loop
        void run_menu();

        int get_height() const;
        int get_width() const;

        void setScene(int i);

};

#endif