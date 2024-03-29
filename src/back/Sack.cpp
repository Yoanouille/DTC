#include "back/Sack.hpp"
#include "back/DomPiece.hpp"
#include "back/TraxPiece.hpp"
#include "back/CarcPiece.hpp"

/**
 * Constructor
 * The sack will assume the role of Garbage Collector :
 * It will allocates the Pieces and delete them at the end of a Game
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
 * Fill the sack corresponding on the gamemodes.
 * 
 * @param size The size of the Sack
 * @param gamemode The gamemode : 0 = Dom, 1 = Trax, 2 = Carcassonne
 * @param perm An integer that represent a certain permutation to execute, 0 = random shuffling
 * @throws UnknownGamemodeException - When gamemode is not between 0 and 2
*/
void Sack::fill(int s, int gamemode, int perm)
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
        initCarcassonne(s,perm);
        break;
    default:
        throw UnknownGamemodeException();
        break;
    }
}

/** Initializes the Sack for a Domino Game */
void Sack::initDom(int s)
{
    size = s;
    for (int i = 0; i < size; i++)
    {
        DomPiece *d = new DomPiece();
        sack.push_back(d);
    }
}

/** Initializes the Sack for a Trax Game */
void Sack::initTrax()
{
    size = 64;
    for (int i = 0; i < size; i++)
    {
        TraxPiece *t = new TraxPiece{};
        sack.push_back(t);
    }
}

/** Initialize the Sack for a Carcassonne Game*/
void Sack::initCarcassonne(int size,int perm)
{
    this->size = size;

    CarcPiece *p24 = new CarcPiece{24};
    CarcPiece *p2 = new CarcPiece{2};
    CarcPiece *p4 = new CarcPiece{4};
    CarcPiece *p5 = new CarcPiece{5};
    CarcPiece *p11 = new CarcPiece{11};
    CarcPiece *p23 = new CarcPiece{23};

    sack.push_back(p24);
    sack.push_back(p2);
    sack.push_back(p4);
    sack.push_back(p5);
    sack.push_back(p11);
    sack.push_back(p23);
        

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

    if(perm == 0) shuffle();
    else permut(perm);
}

/**
 * Executes a permutation on the sack 
 */
void Sack::permut(int perm)
{
    // Randomly generated permutation
    std::vector<int> p;
    if (perm == 1) p = {0, 56, 4, 40, 29, 54, 36, 2, 50, 8, 20, 71, 59, 63, 53, 1, 26, 69, 39, 11, 44, 28, 30, 3, 61, 13, 27, 57, 41, 32, 17, 6, 68, 55, 43, 58, 34, 38, 12, 60, 9, 46, 15, 64, 14, 65, 23, 45, 42, 18, 16, 70, 19, 31, 37, 25, 62, 52, 33, 67, 51, 49, 66, 5, 24, 47, 21, 48, 10, 7, 35, 23};

    // ? Do we need other permutations ?
    
    for(size_t i = 0; i < p.size(); i++)
    {
        int j = p[i];
        Piece *pie = sack[i];
        sack[i] = sack[j];
        sack[j] = pie;
    }

    Piece *pie = sack[46];
    sack[46] = sack[35];
    sack[35] = pie;
}

/** Check if the sack is empty */
bool Sack::isEmpty() { return index >= size; }

/** 
 * ! Only used for Carcassonne
 * Shuffle the Pieces starting from index 1.
 * 0 will always be the starting Piece. 
 */
void Sack::shuffle()
{  
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(sack.begin() + 1,sack.end(),std::default_random_engine{seed});
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
std::ostream &operator<<(std::ostream &out, const Sack &s)
{
    out << "==== Sack : " << s.size << " ====" << std::endl;
    out << "## Pointed index : " << s.index << std::endl;
    for (Piece *p : s.sack)
        out << *p << std::endl;
    out << std::endl;

    return out;
}