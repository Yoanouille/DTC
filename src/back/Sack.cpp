#include "back/Sack.hpp"
using namespace std;

/**
 * Constructor
 * The sack will assume the role of Garbage Collector :
 * It will allocates the Pieces and delete them at the end of a Game
 *
 */
Sack::Sack() : index{0}, size{0}, sack{}{}


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
 * fill the sack corresponding on the gamemodes
 * @param size The size of the Sack
 * @param gamemode The gamemode : 0 = Dom, 1 = Trax, 2 = Carcassonne
*/
void Sack::fill(int s, int gamemode)
{ 
    switch (gamemode)
    {
    case 0:
        initDom(s);
        break;
    case 1:
        initTrax();
        break;
    case 2:
        initCarcassonne();
        shuffle();
        break;
    default:
        throw UnknownGamemodeException();
        break;
    }
}

/**
 * Initializes the Sack for a DomGame
 */
void Sack::initDom(int s)
{
    size = s;
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
    size = 64;
    for (int i = 0; i < size; i++)
    {
        TraxPiece *t = new TraxPiece{};
        sack.push_back(t);
    }
}

void Sack::initCarcassonne()
{
    size = 72;
    CarcPiece *p2 = new CarcPiece{2};
    CarcPiece *p4 = new CarcPiece{4};
    CarcPiece *p5 = new CarcPiece{5};
    CarcPiece *p11 = new CarcPiece{11};
    CarcPiece *p23 = new CarcPiece{23};
    CarcPiece *p24 = new CarcPiece{24};

    sack.push_back(p2);
    sack.push_back(p4);
    sack.push_back(p5);
    sack.push_back(p11);
    sack.push_back(p23);
    sack.push_back(p24);
        

    for (int i = 0; i < 2; i++ ){
        CarcPiece *p1 = new CarcPiece{1};
        CarcPiece *p6 = new CarcPiece{6};
        CarcPiece *p8 = new CarcPiece{8};
        CarcPiece *p10 = new CarcPiece{10};
        CarcPiece *p12 = new CarcPiece{12};
        CarcPiece *p13 = new CarcPiece{13};

        sack.push_back(p1);
        sack.push_back(p6);
        sack.push_back(p8);
        sack.push_back(p10);
        sack.push_back(p12);
        sack.push_back(p13);
    }

    for (int i = 0; i < 3; i++){
        CarcPiece *p3 = new CarcPiece{3};
        CarcPiece *p7 = new CarcPiece{7};
        CarcPiece *p9 = new CarcPiece{9};
        CarcPiece *p14 = new CarcPiece{14};
        CarcPiece *p16 = new CarcPiece{16};
        CarcPiece *p17 = new CarcPiece{17};
        CarcPiece *p18 = new CarcPiece{18};
        CarcPiece *p19 = new CarcPiece{19};

        sack.push_back(p3);
        sack.push_back(p7);
        sack.push_back(p9);
        sack.push_back(p14);
        sack.push_back(p16);
        sack.push_back(p17);
        sack.push_back(p18);
        sack.push_back(p19);
    }

    for(int i = 0; i < 4; i++){
        CarcPiece *p0 = new CarcPiece{0};
        CarcPiece *p22 = new CarcPiece{22};

        sack.push_back(p0);
        sack.push_back(p22);
    }

    for(int i = 0; i < 5; i++){
        CarcPiece *p15 = new CarcPiece{15};
        sack.push_back(p15);
    }

    for(int i = 0; i < 8; i++){
        CarcPiece *p20 = new CarcPiece{20};
        sack.push_back(p20);
    }

    for(int i = 0; i < 9; i++){
        CarcPiece *p21 = new CarcPiece{21};
        sack.push_back(p21);
    }
}

bool Sack::isEmpty()
{
    return index >= size;
}

void Sack::shuffle()
{  
    random_shuffle(sack.begin(),sack.end());
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
ostream &operator<<(ostream &out, const Sack &s)
{
    out << "==== Sack : " << s.size << " ====" << endl;
    out << "## Pointed index : " << s.index << endl;
    for (Piece *p : s.sack)
        out << *p << endl;
    out << endl;

    return out;
}