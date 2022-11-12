#include "Menu.hpp"
#include "FirstScene.hpp"

using namespace sf;

Menu::Menu() : width{1280}, height{720}, sc{nullptr}, image{}, bg{}
{
    init();
}

Menu::~Menu()
{
    if(sc != nullptr) delete sc;
}

void Menu::init()
{
    this->create(sf::VideoMode(width,height), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    this->setPosition(sf::Vector2i(0,0));

    image.loadFromFile("resources/images/bg1.png");
    bg.setTexture(image);
    bg.setScale(0.33, 0.33);

    sc = new FirstScene(*this);

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
    while(this->isOpen())
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