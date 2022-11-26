#include "front/Controller.hpp"

#include <iostream>
using namespace sf;
using namespace std;

// Static getter of the instance
Controller& Controller::getInstance() {
    static Controller INSTANCE;
    return INSTANCE;
}

/**
 * Constructor
 */
Controller::Controller() : clicked{false}, eventMap{}, keyMap{} {}

/**
 * Destructor
 *
 * Is clearing map necessary before destroying ?
 */
Controller::~Controller() { 
    clearActions();
    clearControls();
}

/**
 * Overwrite [EventType,Function] in the map if it exists.
 * Add it to the map otherwise.
 * ! We devs have to make sure to use this function correctly.
 *
 * @param event The event key
 * @param action The function that will be triggered by event
 */
void Controller::setActionOnEvent(Event::EventType event, const function<void()> &action)
{
    eventMap[event] = action;
}

/**
 * Find the action associated with the polledEvent
 * and run it.
 *
 * @param pollEvent The polled event
 */
void Controller::makeAction(Event &polledEvent)
{
    if(eventMap.find(polledEvent.type) != eventMap.end())
        eventMap[polledEvent.type]();
}

/**
 * Bind an action to a Key
 *
 * @param key The key
 * @param action The function trigger when the key is pressed
 */
void Controller::bindActionOnKey(Keyboard::Key key, const function<void()> &action)
{
    keyMap[key] = action;
}

/**
 * Triggers the action associated with a key
 *
 * @param key The Key pressed
 */
void Controller::makeKeyAction(Keyboard::Key key)
{
    if(keyMap.find(key) != keyMap.end())
        keyMap[key]();
}


// ==== Map Clearing functions ==== //
void Controller::clearActions() { eventMap.clear(); }
void Controller::clearControls() { keyMap.clear(); }