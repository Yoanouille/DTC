#ifndef PLAYER_SETTINGS_SCENE_H
#define PLAYER_SETTINGS_SCENE_H

#include <vector>

#include "App.hpp"
#include "Button.hpp"
#include "Scene.hpp"
#include "TextField.hpp"

class PlayerSettingsScene : public Scene {
    private :
        App &app;
        int nbPlayers;

        Button backButton;

        Button plusButton;
        Button minusButton;

        Button submitButton;
        
        std::vector<sf::Text> fieldLabels;
        std::vector<TextField> nameFields;

        void initFields();
        void initButtons();

        void addPlayer();
        void removePlayer();

    public :
        PlayerSettingsScene(App &app,int n);
        virtual ~PlayerSettingsScene();

        // Manage event
        void loop_event() override;

        // Manager the visual of the scene
        void render() override;
};

#endif