#ifndef ASSETS_LOADER_H
#define ASSETS_LOADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

/**
 * It is not recommended to make ressources static 
 * cf. https://en.sfml-dev.org/forums/index.php?topic=27629.0
 * 
 * * We're gonna make Assets class a Singleton
 */
class Assets {
    private: 
        // The singleton instance
        static Assets * instance;

        // Resources stored in the instance
        Font DefaultFont;
        Texture MainMenuBackground;
        Font MainMenuFont;
        Texture TraxTextureRecto;
        Texture TraxTextureVerso;
        Texture Sack;
        Texture RotateLeft;
        Texture Flip;
        Texture CarcPieceTexture;
        int CarcPieceSize;

        Assets();

    public :
        Assets(const Assets &) = delete;
        void operator=(const Assets &) = delete;
        
        static Assets* getInstance();

    friend class App;
    friend class Button;
    friend class MainMenu;
    friend class PlayerSettingsScene;
    friend class MainScene;
    friend class ScoreBoard;
    friend class DrawZone;
    friend class TraxPieceDisplayer;
    friend class DomPieceDisplayer;
    friend class CarcPieceDisplayer;
};

#endif