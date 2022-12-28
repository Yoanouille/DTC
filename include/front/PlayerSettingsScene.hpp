#ifndef PLAYER_SETTINGS_SCENE_H
#define PLAYER_SETTINGS_SCENE_H

#include <vector>

#include "App.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "TextField.hpp"

class PlayerSettingsScene : public Scene {
    private :
        App &app;

        int nbPlayers;

        Button backButton;

        int gamemode;
        Button plusButton;
        Button minusButton;

        Button submitButton;

        float vSpace = 50.0f;
        std::vector<sf::Text> fieldLabels;
        std::vector<TextField> nameFields;

        sf::Vector2f mousepos;

        bool appear;
        bool disp;
        int dispF;
        int nextScene;

        void initFields();
        void initButtons();

        void addPlayer();
        void removePlayer();

    public :
        PlayerSettingsScene(App &app, int nbPlayers, int gamemode);
        virtual ~PlayerSettingsScene();

        // Manage event
        void loop_event() override;

        // Manager the visual of the scene
        void render() override;

        void display();
        void dispose();
        void disposeField();
};

#endif