#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "App.hpp"
#include "back/Game.hpp"

class ScoreBoard {
    private:
        App &app;
        Game *game;
        
        sf::RectangleShape container;

        std::vector<Text> names;
        std::vector<Text> scores;
    public:
        ScoreBoard(App &App);
        virtual ~ScoreBoard();

        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f pos);

        void setGame(Game *game);
        

        sf::Vector2f getSize();
        
        void update();
        void render();
};

#endif