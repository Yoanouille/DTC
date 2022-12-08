#include "front/Button.hpp"
#include <iostream>
using namespace sf;
using namespace std;

int Button::speed = 20;

Button::Button(App &app) : app{app}, container{}, sprite{nullptr}, text{}, font{Assets::getInstance()->DefaultFont} {}

Button::Button(App &app, sf::Texture* imageTexture, std::string text, sf::Font &font, int fontSize, sf::Vector2f containerSize, sf::Vector2f position)
    : app{app}, container{containerSize}, sprite{nullptr}, text{}, font{font}
{
    container.setOutlineThickness(5);
    container.setOutlineColor(Color::Transparent);

    if(imageTexture != nullptr){
        sprite = new Sprite(*imageTexture);
        Vector2u textureSize = imageTexture->getSize();
        sprite->setScale(containerSize.x / textureSize.x, containerSize.y/textureSize.y);
    } else {
        container.setFillColor(Color::Transparent);
    }

    setText(text);
    this->text.setFont(font);
    this->text.setCharacterSize(fontSize); 
    this->text.setFillColor({255,255,255,0});

    setPosition(position.x,position.y);  
}

Button::~Button(){
    if(sprite != nullptr) delete(sprite);
}

// Text Getter and Setter
Text &Button::getText() {
    return text;
}

void Button::setText(string text) {
    this->text.setString(text);
}

// Text Color Getter and Setter
Color Button::getFillColor(){
    return text.getFillColor();
}

void Button::setFillColor(Color c){
    text.setFillColor(c);
}

Sprite *Button::getSprite()
{
    return sprite;
}


FloatRect Button::getGlobalBounds(){
    return container.getGlobalBounds();
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

    if(sprite != nullptr) sprite->setPosition(x,y);
}

/**
 * Check if the button contains a certain point
 * @param point A vector containing mouseposition 
 */
bool Button::contains(Vector2f point){
    return container.getGlobalBounds().contains(point);
}

/**
 * Fade in animation  
 */
bool Button::fadeIn(){
    Color c = text.getFillColor();
    if (c.a <= 255 - speed){
        c.a += speed;
        text.setFillColor(c); 
        return false;
    } 

    c.a = 255;
    text.setFillColor(c); 
    return true;
}

/**
 * Fade out animation
 */
bool Button::fadeOut(){
    Color c = text.getFillColor();
    if(c.a >=  speed){
        c.a -= speed;
        text.setFillColor(c); 
        return false;
    } 

    c.a = 0;
    text.setFillColor(c);
    return true;
}

/**
 * Make the text's Color fade into a given Color 
 * 
 * @param c The given Color
 */
bool Button::fadeInColor(Color col){
    Color c = text.getFillColor();
    int okay = 0;

    // Treats Red
    if (c.r <= col.r - speed)
        c.r += speed;
    else if (c.r >= col.r + speed)
        c.r -= speed;
    else{
        c.r = col.r;
        okay++;
    }
    
    // Treats Green
    if (c.g <= col.g - speed)
        c.g += speed;
    else if (c.g >= col.g + speed)
        c.g -= speed;
        
    else
    {
        c.g = col.g;
        okay++;
    }
       
    // Treats Blue
    if (c.b <= col.b - speed)
        c.b += speed;
    else if (c.b >= col.b + speed)
        c.b -= speed;
    else
    {
        c.b = col.b;
        okay++;
    }

    text.setFillColor(c);

    return (okay == 3);
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
    else if (!Mouse::isButtonPressed(Mouse::Left) || !contains(mousepos)){
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
void Button::render(){
    app.draw(container);
    if (sprite != nullptr) app.draw(*sprite);
    if (text.getString() != "") app.draw(text);
}