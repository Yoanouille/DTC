#include "front/TraxPieceDisplayer.hpp"
using namespace sf;
using namespace std;

/**
 * Static method that loads TraxPiece's Recto and Verso Textures.
 * If Textures can't be loaded, print an error on standard error
 * but the program remains running.
 */
void TraxPieceDisplayer::loadTextures()
{
    if (!TraxPieceDisplayer::textureRecto.loadFromFile("resources/images/traxR.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;

    if (!TraxPieceDisplayer::textureVerso.loadFromFile("resources/images/traxV.png"))
        cerr << "TraxPiece's Texture Loading Failed : traxR.png" << endl;
}

/**
 * Constructor
 */
TraxPieceDisplayer::TraxPieceDisplayer(Menu &m, int x, int y) : PieceDisplayer(m, x, y)
{
    setTexture(&textureRecto);
}

/**
 * Destructor
 */
TraxPieceDisplayer::~TraxPieceDisplayer() {}

/**
 * Rendering function
 */
void TraxPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl)
{
    Vector2f v = {coordinates.x * scl, coordinates.y * scl};
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
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta < 0)
            {
                piece->rotate(false);
                rotate(-90.0);
            }
            else
            {
                piece->rotate(true);
                rotate(90.0);
            }
        }

        // TODO : flip the piece but how ?
    }
}