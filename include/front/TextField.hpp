#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include "App.hpp"

/**
 * I am not going to code this without any help.
 * cf. https://stackoverflow.com/questions/53734084/write-text-input-on-the-screen-in-sfml
 */
class TextField : public sf::Transformable{
    private:
        unsigned int maxSize;
        sf::Font &font;
        sf::Text text;
        sf::RectangleShape container;

        bool clicked;
        bool focus;

    public :
        TextField(unsigned int maxSize, sf::Font &font, sf::Vector2f containerSize, sf::Vector2f position);  

        sf::Text &getText();
        void setText(std::string str);
        void trim();

        void setOutlineColor(Color c); 
        const sf::FloatRect getGlobalBounds()const;
        void setPosition(float x, float y);
        bool contains(sf::Vector2f point);
        void setFocus(bool f);
        void handleInput(sf::Event &e, sf::Vector2f mousepos);

        void render();
};

#endif