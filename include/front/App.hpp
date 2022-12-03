#ifndef APP_H
#define APP_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "AssetsLoader.hpp"
#include "Controller.hpp"
#include "Scene.hpp"

// Class that represents the Window
class App : public sf::RenderWindow
{
private:
    static App * instance;

    // Dimension
    int width;
    int height;

    // current Scene
    Scene *sc;
    // old current Scene
    Scene *old_sc;

    // Sprite of the background, need image
    sf::Sprite bg;

    void init();
    void loop_event();
    void render();

    App();
public:
    static App* getInstance();

    App(const App &) = delete;
    virtual ~App();

    void operator=(const App &) = delete;

    // launch the event loop and the render loop
    void runApp();

    int getHeight() const;
    int getWidth() const;

    void setScene(int i, bool isTraxGame = false);
};

#endif