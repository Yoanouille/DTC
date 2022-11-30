#include "front/AssetsLoader.hpp"

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
    CarcasonneTexture{}
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