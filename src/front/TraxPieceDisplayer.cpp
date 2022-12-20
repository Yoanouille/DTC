#include "front/TraxPieceDisplayer.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 * It is private to prevent for creating more than one Controller.
 * This unique Controller is stored in INSTANCE.
 */
TraxPieceDisplayer::TraxPieceDisplayer(App& app, int x, int y, TraxPiece& p) : PieceDisplayer(app, x, y), piece{p}, dx{0}, dy{0}
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
    while(dx != 0 || dy != 0) this->rotates(false);

    piece.flip();
    setShownSide(piece.isRecto());
}

/**
 * Rendering function
 */
void TraxPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse)
{
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->setPosition(this->getPosition() + Vector2f{scl * dx, scl * dy});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
}

void TraxPieceDisplayer::render(float x, float y, int scl)
{
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->setPosition(x + dx * scl, y + dy * scl);
    app.draw(*this);
}

void TraxPieceDisplayer::rotates(bool clockwise)
{
    piece.rotate(clockwise);

    if(clockwise){
        if((!dx && !dy) || (dx && dy)) dx = !dx;
        else if((dx && !dy) || (!dx && dy)) dy = !dy;

        this->rotate(90.0);
    }    
    else {
        if((!dx && !dy) || (dx && dy)) dy = !dy;
        else if((dx && !dy) || (!dx && dy)) dx = !dx;
        this->rotate(-90.0);
    }
}

Piece &TraxPieceDisplayer::getPiece()
{
    return piece;
}