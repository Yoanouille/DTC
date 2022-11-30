#include "front/TraxPieceDisplayer.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 * It is private to prevent for creating more than one Controller.
 * This unique Controller is stored in INSTANCE.
 */
TraxPieceDisplayer::TraxPieceDisplayer(App &app, TraxPiece& p, int x, int y) : PieceDisplayer(app, x, y, p)
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
        setTexture(&Assets::getInstance()->TraxTextureRecto);
    else
        setTexture(&Assets::getInstance()->TraxTextureVerso);
    
    // Both Images have the same size, we've chosen arbitrarily recto 
    Vector2u textureSize = Assets::getInstance()->TraxTextureRecto.getSize();
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
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
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
    // while (App.pollEvent(event))
    // {
    //     if (event.type == Event::EventType::KeyPressed)
    //         (Controller::getInstance()).makeKeyAction(event.key.code);
    //     else
    //         (Controller::getInstance()).makeAction(event);
    // }
}