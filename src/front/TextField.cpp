#include "front/TextField.hpp"
#include <iostream>
using namespace sf;
using namespace std;

/**
 * Constructor
 * 
 * @param maxSize The size of the field
 * @param font Text's font
 * @param containerSize A vector storing the size of the container
 * @param position A vector storing the coodinates of the top_left corner of the TextField
 */
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
    
    text.setFillColor(Color::Black);
    text.setFont(font);
    text.setPosition(position);
    text.setFillColor(Color::Black);
} 

Text &TextField::getText() {
    return text;
}

/**
 * Setter 
 */
void TextField::setText(string str){
    text.setString(str);
}

/**
 * Set the containers Outline
 * @param c A color 
 */
void TextField::setOutlineColor(Color c){
    container.setOutlineColor(c);
}

/**
 * Trim the contained text 
 */
void TextField::trim(){
    string s = text.getString().toAnsiString();
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") +1);
    setText(s);
}

/**
 * Get the container's global bounds 
 */
const FloatRect TextField::getGlobalBounds() const{
    return container.getGlobalBounds();
}

/**
 * Set the position of the TextField 
 * @param x : abscissa
 * @param y : ordinates
 */
void TextField::setPosition(float x, float y){
    Transformable::setPosition(x, y);
    container.setPosition(x,y);
}

/**
 * Check if the TextField contains a point.
 * 
 * @param point : The coordinates of the point (oftenly mouse position)
 */
bool TextField::contains(sf::Vector2f point){
    return container.getGlobalBounds().contains(point);
}

void TextField::setFocus(bool focus){

    this->focus = focus;
    if (focus)
        this->container.setOutlineColor(sf::Color::Blue);
    else
        container.setOutlineColor(sf::Color::Black);
}

/**
 * Handle the following inputs from the user :
 * - Focus
 * - Text Inputs. 
 * 
 * @param e The polled Event
 * @param mousepos mouse coordinates
 */
void TextField::handleInput(sf::Event &e,Vector2f mousepos){
        
    if (!focus || e.type != sf::Event::TextEntered)
        return;

    if (e.text.unicode == 8)   // Delete key
        text.setString(text.getString().substring(0, text.getString().getSize() - 1));
    else if (text.getString().getSize() < maxSize)
        text.setString(text.getString() + e.text.unicode);
}

/**
 * rendering function 
 */
void TextField::render(){
    App::getInstance()->draw(container);
    App::getInstance()->draw(text);
}