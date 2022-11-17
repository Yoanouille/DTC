#include "front/Menu.hpp"
#include "front/FirstScene.hpp"
#include "front/MainScene.hpp"

using namespace sf;

/** Constructor 
 *  initialize different variable
 */


Menu::Menu() : width{1280}, height{720}, sc{nullptr}, old_sc{nullptr}, image{}, bg{}
{
    init();
}

/** Destructor */
Menu::~Menu()
{
    if (sc != nullptr)
        delete sc;
    if (old_sc != nullptr)
        delete old_sc;
}

/**
 * initialize the Scene
*/
void Menu::init()
{
    this->create(sf::VideoMode(width, height), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    this->setPosition(sf::Vector2i(0, 0));

    image.loadFromFile("resources/images/bg1.png");
    bg.setTexture(image);
    bg.setScale(0.33, 0.33);

    sc = new FirstScene(*this);
    // sc = new MainScene(*this);
}

/**
 * Manage the event in function of the current scene
*/
void Menu::loop_event()
{
    sc->loop_event();
}

/**
 * Manage the render in function of the current scene
*/
void Menu::render()
{
    this->clear();
    this->draw(bg);
    sc->render();
    this->display();
}

/**
 * Launch the 2 main loop (event and render)
*/
void Menu::run_menu()
{
    while (this->isOpen())
    {
        loop_event();
        render();
    }
}

/**
 * getter of the height
 * @return an integer, the height of the window
*/
int Menu::get_height() const
{
    return height;
}

/**
 * getter of the width
 * @return an integer, the width of the window
*/
int Menu::get_width() const
{
    return width;
}

/**
 * set the current scene and store the current scene into old_sc
 * @param i an integer, which identify a scene (1 -> FirstScene, 2 -> MainScene)
*/
void Menu::setScene(int i)
{
    switch (i)
    {
    case 1:
        if (old_sc != nullptr)
            delete old_sc;
        old_sc = sc;
        sc = new FirstScene(*this);
        break;

    case 2:
        if (old_sc != nullptr)
            delete old_sc;
        old_sc = sc;
        sc = new MainScene(*this);
        break;

    default:
        break;
    }
}