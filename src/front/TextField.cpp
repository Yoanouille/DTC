#include "front/TextField.hpp"
using namespace sf;
using namespace std;

TextField::TextField(unsigned int maxSize, Font &font, Vector2f containerSize, Vector2f position) 
    : maxSize{maxSize}, font{font},
      container{Vector2f{containerSize.x * maxSize, containerSize.y}},
      focus{false}
{
    container.setOutlineThickness(2);
    container.setFillColor(Color::White);
    container.setOutlineColor(Color::Black);
    container.setPosition(position); 
    
    text.setFont(font);
    text.setPosition(position);
} 

const std::string TextField::getText() const {
    return text.getString();
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

void TextField::handleInput(sf::Event &e){
    if (!focus || e.type != sf::Event::TextEntered)
        return;

    if (e.text.unicode == 8)   // Delete key
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    else if (text.getString().getSize() < maxSize)
        text.setString(text.getString() + e.text.unicode);
}

void TextField::render(App &app){
    app.draw(container);
    app.draw(text);
}