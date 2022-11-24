#ifndef CONTROLER_H
#define CONTROLER_H

#include <SFML/Graphics.hpp>

/**
 * This class contains data that handle user's inputs
 * (as events)
 *
 * We define template T that represents a lambda function
 * executed by an event.
 */
class Controller
{
private:
    // Boolean that blocks multiple mouse clicks
    // and key combination at the same time
    bool clicked;

    // Maps that associate user's inputs with actions.
    std::map<sf::Event::EventType &, std::function<void>> eventMap;
    std::map<sf::Keyboard::Key &, std::function<void>> keyMap;

public:
    Controller();
    ~Controller();

    // Event handling
    void setActionOnEvent(sf::Event::EventType &event, std::function<void> &action);
    void makeAction(sf::Event &polledEvent);
    void clearActions();

    // KeyBoard inputs handling
    void bindActionOnKey(sf::Keyboard::Key &key, std::function<void> &action);
    void makeKeyAction(sf::Keyboard::Key &k);
    void clearControls();
};

#endif