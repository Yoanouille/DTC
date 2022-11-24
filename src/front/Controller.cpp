#include "front/Controller.hpp"

#include <iostream>
using namespace sf;
using namespace std;

Controller Controller::INSTANCE{};

// Static getter of the instance
Controller Controller::getInstance() { return INSTANCE; }

/**
 * Constructor
 */
Controller::Controller() : clicked{false}, eventMap{}, keyMap{} {}

/**
 * Destructor
 *
 * Is clearing map necessary before destroying ?
 */
Controller::~Controller() { eventMap.clear(); }

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
    bool found = false;
    for (auto &x : eventMap) {
        if (x.first == event) {
            x.second = action;
            break;
        }
    }

    if (!found){
        eventMap.insert({event,action});
    }
}

/**
 * Find the action associated with the polledEvent
 * and run it.
 *
 * @param pollEvent The polled event
 */
void Controller::makeAction(Event &polledEvent)
{
    for (auto &x : eventMap)
        if (x.first == polledEvent.type)
            x.second();
}

/**
 * TODO :Clear the event map
 */
void Controller::clearActions() { eventMap.clear(); }

/**
 * Bind an action to a Key
 *
 * @param key The key
 * @param action The function trigger when the key is pressed
 */
void Controller::bindActionOnKey(Keyboard::Key key, const function<void()> &action)
{
    bool found = false;
    for (auto &x : keyMap) {
        if (x.first == key) {
            x.second = action;
            break;
        }
    }

    if (!found) {
        keyMap.insert({key,action});
    }

    cout << "Action binded." << endl;
}

/**
 * Triggers the action associated with a key
 *
 * @param Key The Key pressed
 */
void Controller::makeKeyAction(Keyboard::Key k)
{
    for (auto &x : keyMap) {
        if (x.first == k) {
            cout << "KeyPressed !" << endl;
            x.second();
        }         
    }  
}

/**
 * Clear the key map
 */
void Controller::clearControls() { keyMap.clear(); }