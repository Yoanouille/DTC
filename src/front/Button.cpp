#include "front/Button.hpp"
#include <iostream>
using namespace sf;
using namespace std;

Button::Button(sf::Texture* imageTexture, std::string text, sf::Font &font, int fontSize, sf::Vector2f containerSize, sf::Vector2f position)
    : container{containerSize}, text{}, font{font}
{
    if(imageTexture != nullptr){
        Vector2u textureSize = imageTexture->getSize();
        container.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
    }
    container.setOutlineThickness(5);
    container.setFillColor(Color::Transparent);
    container.setOutlineColor(Color::Transparent);

    setText(text);
    this->text.setFont(font);
    this->text.setCharacterSize(fontSize); 

    setPosition(position.x,position.y);  
}

Text Button::getText() const{
    return text;
}

void Button::setText(string text) {
    this->text.setString(text);
}

/**
 * Set button's position
 * We move the container to (x,y)
 * The text inside the container is centered 
 */
void Button::setPosition(float x, float y){
    Transformable::setPosition(x, y);
    container.setPosition(x,y);

    FloatRect r = text.getLocalBounds();
    text.setOrigin(r.left + r.width/2.0f ,r.top + r.height/2.0f);
    text.setPosition(x + container.getGlobalBounds().width/2.0f, y + container.getGlobalBounds().height/2.0f);
}

/**
 * Check if the button contains a certain point
 * @param point A vector containing mouseposition 
 */
bool Button::contains(Vector2f point){
    return container.getGlobalBounds().contains(point);
}
    
/**
 * Setter that sets the action 
 * @param action A lambda expression
 */ 
void Button::setActionOnClick(const std::function<void()> &action){
    this->clickAction = action;
}

/**
 * Execute the action if the button is clicked in the right area
 * 
 * @param e An event polled from the event queue
 * @param mousepos The mouse's position
 */ 
void Button::handleClick(Vector2f mousepos){
    if (Mouse::isButtonPressed(Mouse::Left)
        && contains(mousepos)
        && !clicked) {
            this->clickAction();
            clicked = true;
    }
    else if (Mouse::isButtonPressed(Mouse::Left) || !contains(mousepos)){
        clicked = false;
    } 
}

/**
 * Setter that sets the action triggered
 * when the mouse enters in the button.
 * 
 * @param action A lambda expression
 */
void Button::setActionOnMouseEntered(const std::function<void()> &action){
    this->mouseEnteredAction = action;
}

/**
 * Setter that sets the action triggered
 * when the mouse exits from the button 
 * 
 * @param action A lambda expression
 */
void Button::setActionOnMouseExited(const std::function<void(void)> &action){
    this->mouseExitedAction = action;
}

/**
 * Execute the action if the button is clicked in the right area
 * 
 * @param mousepos The mouse's position as a vector
 */ 
void Button::handleHover(Vector2f mousepos){
    if (contains(mousepos))
        this->mouseEnteredAction();
    else 
        this->mouseExitedAction();
}

/**
 * Rendering function 
 */
void Button::render(App &m){
    m.draw(container);
    m.draw(text);
}