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
      container{Vector2f{containerSize.x * maxSize, containerSize.y}},
      clicked{false}, focus{false}
{
    container.setOutlineThickness(2);
    container.setFillColor(Color::White);
    container.setOutlineColor(Color::Black);
    container.setPosition(position); 
    
    text.setFillColor(Color::Black);
    text.setFont(font);
    text.setPosition(position);
} 

/**
 * Getter 
 */
const Text TextField::getText() const {
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

/**
 * Set the Focus of the Textfield
 * 
 * @param f Equals true if the TextField is focused 
 */
void TextField::setFocus(bool f){
    focus = f;
    if (focus)
        setOutlineColor(Color::Blue);
    else
        setOutlineColor(Color::Black);
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
    if (e.type == Event::MouseButtonPressed){
        cout << "Mouse Clicked !" << endl;
        if (e.mouseButton.button == Mouse::Left && contains(mousepos) && !clicked){
            cout << "Focus" << endl;
            setFocus(true);
            clicked = true;
        }
        else if (e.mouseButton.button == Mouse::Left && !contains(mousepos) && !clicked){
            cout << "Unfocus" << endl;
            setFocus(false);
            clicked = true;
        }
    } 
    else if (e.type == Event::MouseButtonReleased){
        cout << "Mouse Released" << endl;
        if (e.mouseButton.button == Mouse::Left)
            clicked = false;
    }
        
    if (e.type == sf::Event::TextEntered){
        cout << "TextEntered " << e.text.unicode <<  endl;
        if (!focus) return;
        if (e.text.unicode == 8)   // Delete key
            text.setString(text.getString().substring(0, text.getString().getSize() - 1));
        else if (text.getString().getSize() < maxSize)
            text.setString(text.getString() + e.text.unicode);
    }
}

/**
 * rendering function 
 */
void TextField::render(App &app){
    app.draw(container);
    app.draw(text);
}