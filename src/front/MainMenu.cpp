#include "front/MainMenu.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 */
MainMenu::MainMenu(App &app) : 
    Scene{}, 
    app{app}, 
    options{3,Button{app,nullptr,"", Assets::getInstance()->MainMenuFont,70,{app.getWidth()/4.0f, app.getHeight()/5.0f},{0,0}}}, 
    disp{false}, appear{true}, mousepos{}, game{-1}
{ 
    init(); 
}

/** Destructor */
MainMenu::~MainMenu() {}

/** Initialize the Scene */
void MainMenu::init()
{   
    // Set the Texts
    options[0].setText("Domino") ;
    options[1].setText("Trax");
    options[2].setText("Carcassonne");

    // Set the Texts' color
    options[0].setFillColor({255,255,255,0});
    options[1].setFillColor({255,255,255,0});
    options[2].setFillColor({255,255,255,0});

    // Set the positions
    for (std::size_t i{}; i < options.size(); i++){
        FloatRect r = options[i].getGlobalBounds();
        options[i].setOrigin(r.width/2.0f, r.height/2.0f );
        options[i].setPosition(app.getWidth()/2.5f, (i + 0.5) * app.getHeight() / (options.size() + 1.0f));
    }
    
    // When the Mouse enters a button 
    // Fade that button's text color into red
    options[0].setActionOnMouseEntered([this](){
        this->options[0].fadeInColor(Color::Red); 
    });

    options[1].setActionOnMouseEntered([this](){ 
        this->options[1].fadeInColor(Color::Red); 
    });

    options[2].setActionOnMouseEntered([this](){ 
        this->options[2].fadeInColor(Color::Red); 
    });
    
    // When the Mouse exits a button
    // Fade that button's text color into white
    options[0].setActionOnMouseExited([this](){ 
        this->options[0].fadeInColor(Color::White); 
    });

    options[1].setActionOnMouseExited([this](){ 
        this->options[1].fadeInColor(Color::White); 
    });

    options[2].setActionOnMouseExited([this](){ 
        this->options[2].fadeInColor(Color::White); 
    });

    // Set Action on Click : Change Scene to PlayerSettingsScene depending on the gamemode :
    // Trax will only authorize two players.

    options[0].setActionOnClick([this](){
        this->dispose();
        this->game = 0;
    });

    options[1].setActionOnClick([this](){ 
        this->dispose();
        this->game = 1;
    });

    options[2].setActionOnClick([this](){
        this->dispose();
        this->game = 2;
    });
}

// Manage event
void MainMenu::loop_event()
{
    Event event;
    while (app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.close();

        // Get the position of the mouse
        mousepos = app.mapPixelToCoords(Mouse::getPosition(app));

    }

    if (!appear && !disp)
    {
        for (size_t i = 0; i < options.size(); i++)
        {
            options[i].handleHover(mousepos);
            options[i].handleClick(mousepos);
        }
    }
}

void MainMenu::render()
{
    if (appear) 
        display();

    if(disp)
    {
        dispose();
        if(!disp) app.setScene(2, game, nullptr);
    }

    for (Button &b : options)
        b.render();
}

/**
 * Disappearing of the scene
 */
void MainMenu::dispose()
{
    disp = true;

    for (Button &b : options){
        if(b.fadeOut())
            disp = false;
    }
}

/**
 * Appearing of the Scene
 */
void MainMenu::display()
{
    for (Button &b : options){
        if(b.fadeIn())
            appear = false;
    }
}