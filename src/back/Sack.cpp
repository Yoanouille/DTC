#include "back/Sack.hpp"
using namespace std;

/**
 * Constructor
 * The sack will assume the role of Garbage Collector :
 * It will allocates the Pieces and delete them at the end of a Game
 *
 * @param size The size of the Sack
 * @param gamemode The gamemode : 0 = Dom, 1 = Trax, 2 = Carcassonne
 */
Sack::Sack(int s, int gamemode) : index{0}, size{s}, sack{}
{
    switch (gamemode)
    {
    case 0:
        initDom();
        break;
    case 1:
        initTrax();
        break;
    case 2:
        initCarcassonne();
        break;
    default:
        throw UnknownGamemodeException();
        break;
    }
}

/**
 * Destructor
 * Frees all the memory allocated by the Pieces before destroying itself.
 */
Sack::~Sack()
{
    for (Piece *p : sack)
        delete (p);
}

/**
 * Initializes the Sack for a DomGame
 */
void Sack::initDom()
{
    for (int i = 0; i < size; i++)
    {
        DomPiece *d = new DomPiece();
        sack.push_back(d);
    }
}

/**
 * Initializes the Sack for a TraxGame
 */
void Sack::initTrax()
{
    for (int i = 0; i < size; i++)
    {
        TraxPiece *t = new TraxPiece{};
        sack.push_back(t);
    }
}

void Sack::initCarcassonne()
{
    // TODO
}

/**
 * Draw a card
 * Takes the index-th element of the array and increment index.
 *
 * @return The card drawn.
 */
Piece *Sack::draw()
{
    Piece *res = sack[index];
    index++;
    return res;
}

/**
 * Printing function
 */
ostream &operator<<(ostream &out, const Sack s)
{
    // TODO
    return out;
}

/**
 * Exception thrown by the Constructor
 */
const char *UnknownGamemodeException::what() const throw()
{
    return "Unknown Gamemode : It should be a number between 0 and 2.";
}