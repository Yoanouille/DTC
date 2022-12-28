#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "App.hpp"

class Button :  public sf::Transformable {
private:
    App &app;

    static int speed;

    // Container : Image will be loaded elsewhere and used in sprite
    sf::RectangleShape container;
    sf::Sprite *sprite;

    // Button's text
    sf::Text text;
    sf::Font &font;

    // Click and Hover Handling members
    bool clicked;
    std::function<void()> clickAction;
    std::function<void()> mouseEnteredAction;
    std::function<void()> mouseExitedAction;

public:
    Button(App &app);
    Button(App &app, sf::Texture* imageTexture, std::string text, sf::Font &font, int fontSize, sf::Vector2f containerSize, sf::Vector2f position);
    ~Button();

    sf::Text &getText();
    void setText(std::string text);

    sf::Color getFillColor();
    void setFillColor(Color c);

    Sprite *getSprite();

    sf::FloatRect getGlobalBounds();
    
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point);

    // Animations
    bool fadeIn();
    bool fadeOut();
    bool fadeInColor(sf::Color c);

    // Handles click
    void setActionOnClick(const std::function<void()> &action);
    void handleClick(sf::Vector2f mousepos);

    // Handles hover
    void setActionOnMouseEntered(const std::function<void()> &action);
    void setActionOnMouseExited(const std::function<void()> &action);
    void handleHover(sf::Vector2f mousepos);

    void setClicked(bool b);

    void render();
};

#endif