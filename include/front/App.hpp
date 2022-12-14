#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "back/Game.hpp"
#include "back/UnknownGamemodeException.hpp"

#include "AssetsLoader.hpp"
#include "Controller.hpp"
#include "Scene.hpp"

enum Gamemode {
    DOMINO = 0,
    TRAX = 1,
    CARCASSONNE = 2
};

// Class that represents the Window
class App : public sf::RenderWindow
{
private:

    // Dimension
    int width;
    int height;

    // current Scene
    Scene *sc;
    // old current Scene
    Scene *old_sc;

    // The Game
    // ! Free the Game at the end 
    Game *game;
    int gamemode;

    // Sprite of the background, need image
    sf::Sprite bg;

    void init();
    void loop_event();
    void render();

public:
    App();
    virtual ~App();

    // launch the event loop and the render loop
    void runApp();

    int getHeight() const;
    int getWidth() const;

    void initGame(int gamemode);
    Game *getGame();
    int getGamemode() const;

    void setScene(int i, int gamemode, std::vector<std::string> *names);

};

#endif