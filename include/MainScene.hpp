#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include "Scene.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <vector>

class MainScene : public Scene
{
    private:
        Menu &menu;
        sf::RectangleShape scoreBoard;
        sf::RectangleShape board;

        int scl;
        sf::Vector2f off;
        sf::RectangleShape rect;


        sf::Vector2i pos_mouse;
        sf::Vector2f mouse_coord;

        std::vector<sf::Vector2f> pos;   

        bool right_pressed;
        sf::Vector2f old_pos;    

        bool disp;
        bool app;

        void init();

        void setup_rect(sf::RectangleShape &r, float x, float y);

    public:
        MainScene(Menu &m);
        virtual ~MainScene();

        void loop_event();
        void render();

        void dispose();
        void display();

};


#endif