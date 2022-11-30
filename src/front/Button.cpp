#include "front/Button.hpp"
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
    container.setOutlineColor(Color::Blue);
    container.setPosition(position);
    
    setText(text);
    this->text.setFont(font);
    this->text.setCharacterSize(fontSize); 

    // Center the text in the container
    Vector2f pos{};
    pos.x = container.getPosition().x + container.getGlobalBounds().width/2 - this->text.getGlobalBounds().width ;
    pos.y = container.getPosition().y + container.getGlobalBounds().height/2 - this->text.getGlobalBounds().height ;
    this->text.setPosition(pos);

}

const string Button::getText() const{
    return text.getString();
}

void Button::setText(string text) {
    this->text.setString(text);
}

void Button::setPosition(float x, float y){
    Transformable::setPosition(x, y);
    setPosition(x,y);
}

bool Button::contains(Vector2f point){
    return container.getGlobalBounds().contains(point);
}
    
/**
 * Setter that sets the action 
 */ 
void Button::setActionOnClick(const std::function<void()> &action){
    this->action = action;
}

/**
 * Execute the action if the button is clicked in the right area
 */ 
void Button::handleClick(Event &e, Vector2f mousepos){
    if (e.type == Event::MouseButtonPressed 
        && contains(mousepos)
        && !clicked) {
            this->action();
            clicked = true;
    }
    else if (e.type == Event::MouseButtonReleased || !contains(mousepos)){
        clicked = false;
    } 
}

void Button::render(App &m){
    m.draw(container);
    m.draw(text);
}