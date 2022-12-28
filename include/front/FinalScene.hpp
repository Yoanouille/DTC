#ifndef FINALSCENE_HPP
#define FINALSCENE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "front/App.hpp"
#include "front/Scene.hpp"
#include "front/Button.hpp"
#include "front/MainScene.hpp"

class FinalScene : public Scene
{
    private:
        App &app;
        Button backToTitle;
        std::vector<Text> texts;

        sf::Vector2f mouse_coord;
        sf::RectangleShape r;
        
        bool appear;
        bool disp;
        bool disp2;

        void init();

    public:
        FinalScene(App &app);
        ~FinalScene();

        void render();
        void loop_event();

        void display();
        void dispose();

};

#endif