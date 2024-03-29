#include "front/ChooseScene.hpp"
#include "back/PlayerCarc.hpp"
#include "back/TraxPiece.hpp"
#include "back/CarcPiece.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 */
ChooseScene::ChooseScene(App &app) : 
    Scene{}, 
    app{app}, 
    options{3,Button{app,nullptr,"", Assets::getInstance()->MainMenuFont,70,{app.getWidth()/4.0f, app.getHeight()/5.0f},{0,0}}}, 
    disp{false}, appear{true}, mousepos{}, names{nullptr}, gamemode{CARCASSONNE}
{ 
    names = new vector<string>{};
    init(); 
}

/** Destructor */
ChooseScene::~ChooseScene() 
{
    delete names;   
}

/** Initialize the Scene */
void ChooseScene::init()
{   
    // Set the Texts
    options[0].setText("Situation 1") ;
    options[1].setText("Situation 2");
    options[2].setText("Situation 3");

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
        this->gamemode = TRAX;
        this->dispose();
        this->sit1();
    });

    options[1].setActionOnClick([this](){ 
        this->dispose();
        this->sit2();
    });

    options[2].setActionOnClick([this](){
        this->dispose();
        this->sit3();
    });
}

/** 
 * Situation 1
 * Test Trax Win conditions and forced moves
 */
void ChooseScene::sit1()
{
    app.initGame(TRAX, 0, 0);
    app.getGame()->addPlayer("One");
    app.getGame()->addPlayer("Two");

    TraxPiece * piece;

    //Vertical Straight line
    for(int i = 0; i < 6; i++)
    {
        piece = (TraxPiece *)(&app.getGame()->draw());
        app.getGame()->place(i, 0, *piece);
    }

    // Line with corners
    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    piece->rotate(true);
    piece->rotate(true);
    app.getGame()->place(0, 1, *piece);

    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    app.getGame()->place(1, 2, *piece);

    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    app.getGame()->place(-1, 1, *piece);

    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    piece->rotate(true);
    piece->rotate(true);
    app.getGame()->place(-1, 0, *piece);

    piece = (TraxPiece *)(&app.getGame()->draw());
    app.getGame()->place(-1, 2, *piece);

    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    app.getGame()->place(0, 2, *piece);

    for(int i = 3; i < 7; i++){
        piece = (TraxPiece *)(&app.getGame()->draw());
        app.getGame()->place(-1, i, *piece);
    }

    piece = (TraxPiece *)(&app.getGame()->draw());
    piece->flip();
    piece->rotate(true);
    app.getGame()->place(1, 1, *piece);
}

/**
 * Situation 2
 * Example of an end of a Carcassonne Game.
 */
void ChooseScene::sit2()
{
    app.initGame(CARCASSONNE, 36 , 1);
    app.getGame()->addPlayer("One");
    app.getGame()->addPlayer("Two");
    app.getGame()->addPlayer("Three");

    CarcPiece *piece = (CarcPiece *)(&app.getGame()->draw());
    piece->placePawn(3, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(0, -1, *piece);

    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(4, 3, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(0, 1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->placePawn(3, 2, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(1, -1, *piece);

    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(1, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(2, -1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(1, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(1, 1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->placePawn(3, 1, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(0, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->placePawn(2, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(1, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->placePawn(3, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(2, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(4, 3, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(0, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(1, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(1, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->rotate(false);
    app.getGame()->place(1, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->rotate(false);
    piece->placePawn(0, 1, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(1, 5, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(2, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(0, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(2, 5, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->placePawn(4, 3, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(3, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    app.getGame()->place(2, 1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->rotate(true);
    piece->rotate(true);
    piece->rotate(false);
    piece->placePawn(3, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(-1, 1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(true);
    piece->placePawn(2, 1, 2);
    ((PlayerCarc *)(app.getGame()->getPlayers()[2]))->addPawn(-1);
    app.getGame()->place(3, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(3, 5, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->placePawn(4, 3, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(4, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(0, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    app.getGame()->place(0, 5, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(-1, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    app.getGame()->place(-1, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->rotate(false);
    piece->placePawn(3, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(3, 1, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->placePawn(2, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(-2, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(4, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->rotate(false);
    piece->placePawn(2, 1, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(3, 0, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->placePawn(2, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(5, 2, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    app.getGame()->place(2, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->rotate(false);
    app.getGame()->place(-2, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->placePawn(2, 1, 1);
    ((PlayerCarc *)(app.getGame()->getPlayers()[1]))->addPawn(-1);
    app.getGame()->place(5, 3, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->rotate(false);
    app.getGame()->place(4, 4, *piece);
    
    piece = (CarcPiece *)(&app.getGame()->draw());
    piece->rotate(false);
    piece->rotate(false);
    piece->placePawn(4, 3, 0);
    ((PlayerCarc *)(app.getGame()->getPlayers()[0]))->addPawn(-1);
    app.getGame()->place(3, 4, *piece);
}

/**
 * Situation 3
 * ? What to test ?
 */
void ChooseScene::sit3()
{
    app.initGame(CARCASSONNE, 72,2);
    app.getGame()->addPlayer("One");
    app.getGame()->addPlayer("Two");
    app.getGame()->addPlayer("Three");
}

// Manage event
void ChooseScene::loop_event()
{
    Event event{};
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

void ChooseScene::render()
{
    if (appear) 
        display();

    if(disp)
    {
        dispose();
        if(!disp){
            if(gamemode == CARCASSONNE)
                app.setScene(3, CARCASSONNE, names);
            else if (gamemode == TRAX)
                app.setScene(3,TRAX,names);
        }
    }

    for (Button &b : options)
        b.render();
}

/**
 * Disappearing of the scene
 */
void ChooseScene::dispose()
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
void ChooseScene::display()
{
    for (Button &b : options){
        if(b.fadeIn())
            appear = false;
    }
}