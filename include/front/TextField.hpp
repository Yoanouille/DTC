#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>

/**
 * I am not going to code this without any help.
 * cf.
 * https://stackoverflow.com/questions/53734084/write-text-input-on-the-screen-in-sfml
 */
class TextField : public sf::Transformable, public sf::Drawable{
    private:
        unsigned int maxSize;
        sf::Font &font;
        std::string text;
        sf::RectangleShape container;
        bool focus;

    public :
        TextField(unsigned int maxSize, sf::Font &font);  

        const std::string getText() const;
        void setPosition(float x, float y);
        bool contains(sf::Vector2f point);
        void setFocus(bool focus);
        void handleInput(sf::Event e);
};

#endif