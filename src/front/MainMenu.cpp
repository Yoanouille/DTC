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
    disp{false}, 
    appear{true}, 
    speed{20}
{ 
    init(); 
}

/** Destructor */
MainMenu::~MainMenu() {}

/** Initialize the Scene */
void MainMenu::init()
{   
    options[0].setText("Domino") ;
    options[1].setText("Trax");
    options[2].setText("Carcassonne");

    for (std::size_t i{}; i < options.size(); i++){
        FloatRect r = options[i].getGlobalBounds();
        options[i].setOrigin(r.width/2.0f, r.height/2.0f );
        options[i].setPosition(app.getWidth()/2.5f, (i + 0.5) * app.getHeight() / (options.size() + 1.0f));
    }
    
    // TODO : Make Animation works
    options[0].setActionOnMouseEntered([this](){ this->options[0].fadeInColor(Color::Red); });
    options[1].setActionOnMouseEntered([this](){ this->options[1].fadeInColor(Color::Red); });
    options[2].setActionOnMouseEntered([this](){ this->options[2].fadeInColor(Color::Red); });
    
    // TODO : Make Animation works
    options[0].setActionOnMouseExited([this](){ this->options[0].fadeInColor(Color::White); });
    options[1].setActionOnMouseExited([this](){ this->options[1].fadeInColor(Color::White); });
    options[2].setActionOnMouseExited([this](){ this->options[2].fadeInColor(Color::White); });

    // Set Action on Click : Change Scene to PlayerSettingsScene depending on the gamemode :
    // Trax will only authorize two players.

    // ? How to make the Scene fade out without any problem ?
    options[0].setActionOnClick([this](){
        this->dispose();
        this->app.setScene(2);
    });

    options[1].setActionOnClick([this](){ 
        this->dispose();
        this->app.setScene(2,true);
    });

    options[2].setActionOnClick([this](){
        this->dispose();
        this->app.setScene(2);
    });

    // // Setup texts
    // options = {"Domino", "Trax", "Carcassonne"};
    // texts.resize(options.size());
    // for (std::size_t i{}; i < texts.size(); ++i)
    // {
    //     texts[i].setFont(Assets::getInstance()->MainMenuFont);
    //     texts[i].setString(options[i]);
    //     texts[i].setCharacterSize(75);
    //     Color c{255, 255, 255, 0};
    //     texts[i].setFillColor(c);
    //     FloatRect r = texts[i].getGlobalBounds();
    //     texts[i].setOrigin(0.5 * r.width, 0.5 * r.height);
    //     texts[i].setPosition(app.getWidth() / 2.0f, (i + 1) * app.getHeight() / (options.size() + 1));
    // }
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
        Vector2f mousepos = app.mapPixelToCoords(Mouse::getPosition(app));

        if (!appear && !disp)
            for (size_t i = 0; i < options.size(); i++)
            {
                options[i].handleHover(mousepos);
                options[i].handleClick(mousepos);
               
                // if (texts[i].getGlobalBounds().contains(mouse_coord))
                // {
                //     // Change Scene to a Scene that sets players.
                //     // maybe strore some variable to know which game it is
                //     cout << "Changement de Scene" << endl;
                //     disp = true;
                // }
         }
    }

    // Actions on Hover 
    // Color c = this->options[0].getText().getFillColor();
        // while(c != Color::Red){
        //     if (c.g >= this->speed)
        //         c.g -= this->speed; // speed
        //     if (c.b >= this->speed)
        //         c.b -= this->speed; // speed

        //    this->options[0].getText().setFillColor(c);
        // }

    // Color c = this->options[0].getText().getFillColor();
        // while(c != Color::Red){
        //     if (c.g < 255 - this->speed)
        //         c.g += this->speed; // speed
        //     if (c.b < 255 - this->speed)
        //         c.b += this->speed; // speed

        //    this->options[0].getText().setFillColor(c);
        // }
}

void MainMenu::render()
{
    if (appear) 
        display();

    for (Button &b : options)
        b.render();
}

/**
 * Disappearing of the scene
 */
void MainMenu::dispose()
{
    if (!disp)
        return;

    for (Button &b : options)
        b.fadeOut();
}

/**
 * Appearing of the Scene
 */
void MainMenu::display()
{
    for (Button &b : options)
        b.fadeIn();
}