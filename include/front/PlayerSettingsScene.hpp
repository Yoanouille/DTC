#ifndef PLAYER_SETTINGS_SCENE_H
#define PLAYER_SETTINGS_SCENE_H

#include "Scene.hpp"

class PlayerSettingsScene : public Scene {
    private :
        int nbPlayers;


    public :
        PlayerSettingsScene(int n);

        // Manage event
        void loop_event() override;

        // Manager the visual of the scene
        void render() override;
};

#endif