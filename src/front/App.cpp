#include "front/App.hpp"
#include "front/MainMenu.hpp"
#include "front/PlayerSettingsScene.hpp"
#include "front/MainScene.hpp"

using namespace sf;

/** 
 * Constructor
 * Initialize different variables.
 */
App::App() : width{1280}, height{720}, sc{nullptr}, old_sc{nullptr}, bg{}
{  
    init();
}

/** Destructor */
App::~App()
{
    if (sc != nullptr)
        delete sc;
    if (old_sc != nullptr)
        delete old_sc;
}

/**
 * initialize the Scene
 */
void App::init()
{
    this->create(sf::VideoMode(width, height), "DTC", sf::Style::Titlebar | sf::Style::Close);
    this->setPosition(sf::Vector2i(0, 0));

    bg.setTexture(Assets::getInstance()->MainMenuBackground);
    bg.setScale(0.33, 0.33);

    sc = new MainMenu(*this);
}

/**
 * Manage the event depending on the current scene
 */
void App::loop_event()
{
    sc->loop_event();
}

/**
 * Manage the render depending on the current scene
 */
void App::render()
{
    this->clear();
    this->draw(bg);
    sc->render();
    this->display();
}

/**
 * Launch the 2 main loop (event and render)
 */
void App::runApp()
{
    sf::Clock clock;
    float lastTime = 0;
   
    while (this->isOpen())
    {
        //Settings for the 30FPS
        float currentTime = clock.restart().asSeconds();
        lastTime += currentTime;
        if(lastTime >= 1.0 / 30) {
            float fps = 1.f / (lastTime);
            //std::cout << fps << std::endl;
            lastTime = currentTime;
            loop_event();
            render();
        }
    }
}

/**
 * Getter of the height
 * @return An integer, the height of the App
 */
int App::getHeight() const
{
    return height;
}

/**
 * Getter of the width
 * @return An integer, the width of the App
 */
int App::getWidth() const
{
    return width;
}

/**
 * Set the current scene and store the current scene into old_sc
 * @param i An integer, which identify a scene :
 *  1 -> MainMenu
 *  2 -> PlayerSettingsScene 
 *  3 -> MainScene
 */
void App::setScene(int i)
{
    switch (i)
    {
    case 1:
        if (old_sc != nullptr)
            delete old_sc;
        old_sc = sc;
        sc = new MainMenu(*this);
        break;

    case 2:
        if (old_sc != nullptr)
            delete old_sc;
        old_sc = sc;
        sc = new PlayerSettingsScene(*this,2);
        break;

    case 3:
        if (old_sc != nullptr)
            delete old_sc;
        old_sc = sc;
        sc = new MainScene(*this);
        break;

    default:
        break;
    }
}