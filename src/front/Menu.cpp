#include "front/Menu.hpp"
#include "front/FirstScene.hpp"
#include "front/MainScene.hpp"

using namespace sf;

Menu::Menu() : width{1280}, height{720}, sc{nullptr}, old_sc{nullptr}, image{}, bg{}
{
    init();
}

Menu::~Menu()
{
    if (sc != nullptr)
        delete sc;
    if (old_sc != nullptr)
        delete old_sc;
}

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

void Menu::loop_event()
{
    sc->loop_event();
}

void Menu::render()
{
    this->clear();
    this->draw(bg);
    sc->render();
    this->display();
}

void Menu::run_menu()
{
    while (this->isOpen())
    {
        loop_event();
        render();
    }
}

int Menu::get_height() const
{
    return height;
}

int Menu::get_width() const
{
    return width;
}

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