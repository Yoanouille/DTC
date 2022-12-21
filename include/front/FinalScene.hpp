#ifndef FINALSCENE_HPP
#define FINALSCENE_HPP

#include <SFML/Graphics.hpp>
#include "front/AssetsLoader.hpp"
#include "front/Button.hpp"
#include "front/Scene.hpp"
#include "front/App.hpp"
#include "front/MainScene.hpp"

#include <iostream>
#include <vector>

class FinalScene : public Scene
{
    private:
        App &app;
        Button backToTitle;
        std::vector<Text> texts;

        sf::Vector2f mouse_coord;
        
        void init();

    public:
        FinalScene(App &app);
        ~FinalScene();

        void render();
        void loop_event();

};

#endif