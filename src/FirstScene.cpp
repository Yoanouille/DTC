#include "FirstScene.hpp"

using namespace sf;
using namespace std;

FirstScene::FirstScene(Menu &m) : Scene{}, menu{m}, font{}, options{}, texts{}, pos_mouse{}, mouse_coord{} 
{
    init();
}

FirstScene::~FirstScene()
{

}



void FirstScene::init()
{
    font.loadFromFile("resources/font/Hylia.otf");

    options = {"Domino", "Trax", "Carcassonne"};
    texts.resize(options.size());
    for (std::size_t i{}; i < texts.size(); ++i){
        texts[i].setFont(font); 
        texts[i].setString(options[i]); 
        texts[i].setCharacterSize(75);
        texts[i].setOutlineColor(sf::Color::White);
        FloatRect r = texts[i].getGlobalBounds();
        texts[i].setOrigin(0.5 * r.width , 0.5 * r.height);
        texts[i].setPosition(menu.get_width() / 2, (i + 1) * menu.get_height() / (options.size() + 1));
    }
}


void FirstScene::loop_event()
{
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            menu.close();

        pos_mouse = Mouse::getPosition(menu);
        mouse_coord = menu.mapPixelToCoords(pos_mouse);


        if(Mouse::isButtonPressed(Mouse::Left))
            for(size_t i = 0; i < texts.size(); i++)
            {
                if(texts[i].getGlobalBounds().contains(mouse_coord))
                {
                    //Changer de scene vers la bonne
                    cout << "Changement de Scene" << endl;
                }
            }

    }

    for(size_t i = 0; i < texts.size(); i++)
    {
        if(texts[i].getGlobalBounds().contains(mouse_coord))
        {
            Color c = texts[i].getFillColor();     
            if(c.g >= 1) c.g -= 1;
            if(c.b >= 1) c.b -= 1;
            
            texts[i].setFillColor(c);

        } else {
            Color c = texts[i].getFillColor();     
            if(c.g < 255) c.g += 1;
            if(c.b < 255) c.b += 1;
            
            texts[i].setFillColor(c);
        }
    }
}



void FirstScene::render()
{
    for(Text &t : texts)
    {
        menu.draw(t);
    }
}