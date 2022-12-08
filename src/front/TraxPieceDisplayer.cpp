#include "front/TraxPieceDisplayer.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 * It is private to prevent for creating more than one Controller.
 * This unique Controller is stored in INSTANCE.
 */
TraxPieceDisplayer::TraxPieceDisplayer(App& app, int x, int y, TraxPiece& p) : PieceDisplayer(app, x, y), piece{p}
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


void TraxPieceDisplayer::rotate(bool clockwise)
{
    piece.rotate(clockwise);
    //TODO Rotate image
}