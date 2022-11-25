#ifndef CONTROLER_H
#define CONTROLER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <utility>

/**
 * This class contains data that handle user's inputs
 * (as events)
 */
class Controller
{
private:
    static Controller INSTANCE;

    // Boolean that blocks multiple mouse clicks
    // and key combination at the same time
    bool clicked;

    // Maps that associate user's inputs with actions.
    std::map<const sf::Event::EventType, std::function<void()>> eventMap;
    std::map<const sf::Keyboard::Key, std::function<void()>> keyMap;

public:
    Controller();
    ~Controller();

    // Static instance of the Controller
    static Controller getInstance();

    // Event handling
    void setActionOnEvent(const sf::Event::EventType event, const std::function<void()> &action);
    void makeAction(sf::Event &polledEvent);
    void clearActions();

    // KeyBoard inputs handling
    void bindActionOnKey(sf::Keyboard::Key key,  const std::function<void()> & action);
    void makeKeyAction(sf::Keyboard::Key k);
    void clearControls();
};

#endif