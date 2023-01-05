#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "App.hpp"
#include "back/Game.hpp"
#include "back/PlayerCarc.hpp"

class ScoreBoard {
    private:
        static const Color color[4];

        App &app;
        Game *game;
        
        sf::RectangleShape container;

        std::vector<Text> names;
        std::vector<Text> scores;
        std::vector<Text> nbPawns;

        bool appear;
    
    public:
        ScoreBoard(App &App);
        virtual ~ScoreBoard();

        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f pos);

        void setGame(Game *game);
        

        sf::Vector2f getSize();
        
        void update();
        void render();

        void display();
};

#endif