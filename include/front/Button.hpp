#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "App.hpp"

class Button :  public sf::Transformable {
private:

    // Container : Image will be loaded statically elsewhere.
    sf::RectangleShape container;

    // Button's text
    sf::Text text;
    sf::Font &font;

    bool clicked;
    std::function<void()> clickAction;
    std::function<void()> mouseEnteredAction;
    std::function<void()> mouseExitedAction;

public:
    Button(sf::Texture* imageTexture, std::string text, sf::Font &font, int fontSize, sf::Vector2f containerSize, sf::Vector2f position);
    
    sf::Text getText() const;
    void setText(std::string text);
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point);

    // Handles click
    void setActionOnClick(const std::function<void()> &action);
    void handleClick(sf::Event &e, sf::Vector2f mousepos);

    // Handles hover
    void setActionOnMouseEntered(const std::function<void()> &action);
    void setActionOnMouseExited(const std::function<void()> &action);
    void handleHover(sf::Vector2f mousepos);

    void render(App &app);
};

#endif