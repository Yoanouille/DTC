#include "front/AssetsLoader.hpp"
using namespace sf;

Assets * Assets::instance = nullptr;
/**
 * Load all fonts and textures needed.
 * 
 * If an eror occurs, print a message on stderr but the program keeps running.
 */
Assets::Assets() : 
    DefaultFont{},
    MainMenuBackground{},
    MainMenuFont{},
    TraxTextureRecto{},
    TraxTextureVerso{},
    Sack{},
    RotateLeft{},
    Flip{},
    CarcPieceTexture{},
    CarcPieceSize{86}
{
    if (!DefaultFont.loadFromFile("resources/font/Arial.ttf"))
        cerr << "Couldn't load DefaultFont." << endl;

    if (!MainMenuBackground.loadFromFile("resources/images/bg1.png"))
        cerr << "Couldn't load MainMenuBackground" << endl;

    if (!MainMenuFont.loadFromFile("resources/font/Hylia.otf")){
        cerr << "Couldn't load MainMenuFont, using defaultFont" << endl;
        MainMenuFont = DefaultFont;
    }

    if (!TraxTextureRecto.loadFromFile("resources/images/traxR.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;

    if (!TraxTextureVerso.loadFromFile("resources/images/traxV.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;

    if (!Sack.loadFromFile("resources/images/sack.png"))
        cerr << "Loading Failed : sack.png" << endl;

    if (!RotateLeft.loadFromFile("resources/images/rotateLeft.png"))
        cerr << "Loading Failed : rotateLeft.png" << endl;

    if (!Flip.loadFromFile("resources/images/flip.png"))
        cerr << "Loading Failed : flip.png" << endl;

    if (!CarcPieceTexture.loadFromFile("resources/images/CPiece.png"))
        cerr << "Loading Failed : CPiece.png" << endl;
}

/**
 * Returns the instance of Asset
 * ! Have to free the pointer somewhere 
 */
Assets* Assets::getInstance(){
    if(instance == nullptr)
        instance = new Assets();
    return instance;
}