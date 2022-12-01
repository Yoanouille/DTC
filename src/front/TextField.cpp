#include "front/TextField.hpp"
using namespace sf;
using namespace std;

TextField::TextField(unsigned int maxSize, Font &font, Vector2f containerSize, Vector2f position) 
    : maxSize{maxSize}, font{font},
      container{},
      focus{false}
{
    container.setSize(Vector2f{containerSize.x * maxSize, containerSize.y});
    container.setOutlineThickness(3);
    container.setFillColor(Color::White);
    container.setOutlineColor(Color::Black);
    container.setPosition(position); 
    
    text.setFont(font);
    text.setPosition(position);
    text.setFillColor(Color::Black);
} 

Text &TextField::getText() {
    return text;
}

void TextField::setText(string str){
    text.setString(str);
}

void TextField::setOutlineColor(Color c){
    container.setOutlineColor(c);
}

void TextField::trim(){
    string s = text.getString().toAnsiString();
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") +1);
    setText(s);
}

const FloatRect TextField::getGlobalBounds() const{
    return container.getGlobalBounds();
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
    {
        this->container.setOutlineColor(sf::Color::Blue);
    }
    else
    {
        container.setOutlineColor(sf::Color::Black);
    }
}

void TextField::handleInput(sf::Event &e,Vector2f mousepos){
        
    if (!focus || e.type != sf::Event::TextEntered)
    {
        return;
    }

    if (e.text.unicode == 8)   // Delete key
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    else if (text.getString().getSize() < maxSize)
    {
        text.setString(text.getString() + e.text.unicode);
    }
}

void TextField::render(App &app){
    app.draw(container);
    app.draw(text);
}