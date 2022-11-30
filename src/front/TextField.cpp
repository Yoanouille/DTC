#include "front/TextField.hpp"
using namespace sf;
using namespace std;

TextField::TextField(unsigned int maxSize, Font &font) 
    : maxSize{maxSize}, font{font},
      container{Vector2f{15 * maxSize, 20}},
      focus{false}
{
    container.setOutlineThickness(2);
    container.setFillColor(Color::White);
    container.setOutlineColor(Color::Black);
    container.setPosition(this->getPosition()); 
} 

const std::string TextField::getText() const {
    return text;
}

void TextField::setPosition(float x, float y){
    Transformable::setPosition(x, y);
    container.setPosition(x,y);
}

bool TextField::contains(sf::Vector2f point){
    return container.getGlobalBounds().contains(point);
}

void TextField::setFocus(bool focus){
    this->focus = focus;
    if (focus)
        container.setOutlineColor(sf::Color::Blue);
    else
        container.setOutlineColor(sf::Color::Black);
}

void TextField::handleInput(sf::Event e){
    if (!focus || e.type != sf::Event::TextEntered)
        return;

    if (e.text.unicode == 8)   // Delete key
        text = text.substr(0, text.size() - 1);
    else if (text.size() < maxSize)
        text += e.text.unicode;
}