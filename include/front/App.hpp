#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "AssetsLoader.hpp"
#include "Scene.hpp"

#include "back/Game.hpp"
#include "back/UnknownGamemodeException.hpp"


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
    Game *game;
    int gamemode;

    // Sprite of the background, need image
    sf::Sprite bg;

    void init(int mode);
    void loop_event();
    void render();

public:
    App(int mode);
    virtual ~App();

    // launch the event loop and the render loop
    void runApp(int i);

    int getHeight() const;
    int getWidth() const;

    void initGame(int gamemode, int size, int perm);
    Game *getGame();
    int getGamemode() const;

    Scene *getOldScene() const;

    void setScene(int i, int gamemode, std::vector<std::string> *names);

};

#endif