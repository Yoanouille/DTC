#include "front/TraxPieceDisplayer.hpp"
using namespace sf;
using namespace std;

/**
 * Initializing static fields.
 * They will be set with loadTextures
 */
Texture TraxPieceDisplayer::textureRecto;
Texture TraxPieceDisplayer::textureVerso;

/**
 * Static method that loads TraxPiece's Recto and Verso Textures.
 * If Textures can't be loaded, print an error on standard error
 * but the program continue its execution.
 */
void TraxPieceDisplayer::loadTextures()
{
    if (!TraxPieceDisplayer::textureRecto.loadFromFile("resources/images/traxR.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;

    else if (!TraxPieceDisplayer::textureVerso.loadFromFile("resources/images/traxV.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;
    else
        cout << "TraxPiece's Textures loaded ! " << endl;
}

/**
 * Constructor
 * It is private to prevent for creating more than one Controller.
 * This unique Controller is stored in INSTANCE.
 */
TraxPieceDisplayer::TraxPieceDisplayer(Menu &m, TraxPiece& p, int x, int y) : PieceDisplayer(m, x, y), piece{p}
{
    setShownSide(true);
}

/**
 * Destructor
 */
TraxPieceDisplayer::~TraxPieceDisplayer() {}

/**
 * Private method that sets the shown side of the Piece
 * @param recto A boolean that indicates if the displayer have to show Recto or Verso
 */
void TraxPieceDisplayer::setShownSide(bool recto){
    if(recto)
        setTexture(&textureRecto);
    else
        setTexture(&textureVerso);
    
    // Both Images have the same size, we've chosen arbitrarily recto 
    Vector2u textureSize = textureRecto.getSize();
    setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
}

/**
 * Flip the Piece 
 * Adapt the view : we have to take the rotation into consideration. 
 */
void TraxPieceDisplayer::flip(){
    ((TraxPiece&)piece).flip();
    setShownSide(((TraxPiece&)piece).isRecto());
}

/**
 * Rendering function
 */
void TraxPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{
    Vector2f v{coordinates.x * scl, coordinates.y * scl};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({scl, scl});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        menu.draw(*this);
}

/**
 * Event loop
 */
void TraxPieceDisplayer::loop_event()
{
    // // Set up actions
    // (Controller::getInstance()).bindActionOnKey(Keyboard::Left, [this](){ 
    //     this->rotate(false);
    // });

    // (Controller::getInstance()).bindActionOnKey(Keyboard::Left, [this](){
    //     this->rotate(true);
    // });

    // (Controller::getInstance()).bindActionOnKey(Keyboard::Up, [this](){ 
    //     this->flip(); 
    // });

    // (Controller::getInstance()).bindActionOnKey(Keyboard::Down, [this](){
    //      this->flip();
    // });

    // cout << "Controller set" << endl;

    // // Event loop
    // Event event;
    // while (menu.pollEvent(event))
    // {
    //     if (event.type == Event::EventType::KeyPressed)
    //         (Controller::getInstance()).makeKeyAction(event.key.code);
    //     else
    //         (Controller::getInstance()).makeAction(event);
    // }
}