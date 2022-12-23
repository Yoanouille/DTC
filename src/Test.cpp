#include "back/DomPiece.hpp"
#include "back/TraxPiece.hpp"
#include "back/Sack.hpp"
#include "back/VecZ.hpp"
#include "back/Game.hpp"
#include "back/Trax.hpp"
#include "back/Carcassonne.hpp"

#include <iostream>
#include <string>
using namespace std;

/**
 * Test function for DomPiece
 *
 * CheckList :
 * 1- Correctly generated ?
 * 2- connectable works ?
 * 3- getEarnedValue works ?
 *
 * ! Tests have been realized on DomPieces with numbers between 0 and 2 in order to increase the prbability of having matching sides.
 */
void testDomPiece()
{
    // 1
    DomPiece dom1{};
    DomPiece dom2{};

    cout << "==== Dom1 ====" << endl;
    cout << dom1 << endl;
    cout << "==== Dom2 ====" << endl;
    cout << dom2 << endl;

    // 2
    // cout << "==== Connectable on Dom2 ====" << endl;
    // for (int i = 0; i < 4; i++)
    //     cout << "Direction " << i << ":" << dom1.connectable((Piece &)dom2, i) << endl;

    // 3
    // cout << "==== getEarnedValue on Dom2 ====" << endl;
    // for (int i = 0; i < 4; i++)
    //     cout << "Direction " << i << ":" << dom1.getEarnedValue((Piece &)dom2, i) << endl;
}

/**
 * Test function for TraxPiece
 *
 * It just verifies that the two types of pieces are correctly generated and flip works.
 */
void testTraxPiece()
{
    TraxPiece t1{};

    // Test recto
    cout << "==== Recto ==== " << endl;
    cout << t1 << endl;

    // Test verso
    t1.flip();
    cout << "==== Verso ====" << endl;
    cout << t1 << endl;

    t1.flip();
    cout << "==== Recto again ====" << endl;
    cout << t1 << endl;
}

/**
 * Test function dor Sack
 *
 * Generates a Sack for each game.
 * Checklist :
 * - All the Pieces are correctly generated ?
 * - Unknown Gamemode ?
 * - draw function works ?
 * - Memory test ?
 *
 * - For Carcassonne : shuffle works ?
 */
void testSack()
{
    Sack domSack{};
    domSack.fill(5,0,0);

    Sack traxSack{};
    domSack.fill(0,1,0);

    Sack carcSack{};
    carcSack.fill(0,2,0);

    cout << "---- DomPieces ----" << endl;
    cout << domSack << endl;
    cout << "---- TraxPieces ----" << endl;
    cout << traxSack << endl;
    cout << "---- CarcPieces ----" << endl;
    cout << carcSack << endl;

    cout << "==== Unknwown Gamemode Test ====" << endl;
    try
    {
        Sack unknown{};
        unknown.fill(5,3,0);
        cout << " Failure" << endl;
    }
    catch (UnknownGamemodeException &e)
    {
        cout << " Success" << endl;
    }

    cout << "==== Draw Test ====" << endl;
    cout << *(domSack.draw()) << endl;
    cout << "---- DomSack after draw ----" << endl;
    cout << domSack << endl;
}

/**
 * Function Test for VecZ
 * First test with a simple vector
 * Second test with a double vector
 */
void testVecZ()
{
    cout << "==== VecZ Test ====" << endl;
    cout << "---- Simple VecZ ----" << endl;
    VecZ<int> v;
    v.insert(0, 35);
    v.insert(-1, 2);
    v.insert(-2, 3);
    v.insert(-3, 5);
    v.insert(1, 4);
    v.insert(8, 24);
    v.insert(10, 24);
    v.insert(15, 24);
    v.insert(13, 24);
    v.insert(21, 24);
    v.insert(22, 24);
    v.insert(-6, 7);
    v.insert(-10, 800);
    v.print();

    cout << "---- Double VecZ ----" << endl;

    VecZ<VecZ<int>> v2D;
    for(int i = -10; i <= 10; i++)
        for(int j = -10; j <= 10; j++)
            v2D[i][j] = 10 * i + j;

    for(int i = v2D.get_min(); i <= v2D.get_max(); i++)
        v2D[i].print();
}

void testTrax_1()
{
    Game *g = new Trax();  
    Trax *t = (Trax *)g;
    bool DF = false;

    g->addPlayer("Yoan");
    g->addPlayer("Nicolas");

    Piece &p = g->draw();
    cout << p << endl;
    cout << g->canPlace(0, 0, p) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(0, 0, p);
    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    TraxPiece &p2 = (TraxPiece &)g->draw();
    p2.flip();
    cout << p2 << endl;
    cout << g->canPlace(0, -1, p2) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(0, -1, p2);
    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    TraxPiece &p3 = (TraxPiece &)g->draw();
    p3.flip();
    p3.rotate(true);
    cout << p3 << endl;
    cout << g->canPlace(-1, -1, p3) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(-1,-1,p3);
    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    Piece &p4 = g->draw();
    cout << p4 << endl;
    cout << g->canPlace(-1, 0, p4) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(-1, 0, p4);
    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    TraxPiece &p5 = (TraxPiece &)g->draw();
    p5.flip();
    p5.rotate(false);
    p5.rotate(false);
    cout << p5 << endl;
    cout << g->canPlace(-1, 1, p5) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(-1, 1, p5);
    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    TraxPiece &p6 = (TraxPiece &)g->draw();
    p6.flip();
    p6.rotate(false);
    cout << p6 << endl;
    cout << g->canPlace(0, 1, p6) << endl;
    cout << g->getPlayers()[g->getCurrentPlayer()]->getName() << endl;
    g->place(0, 1, p6);

    DF =  t->DFS(1);
    cout << "DFS : " << DF << endl;

    delete g; 
}

void testTrax_2()
{
    Game *g = new Trax();
    Trax *t = (Trax *)g;
    bool DF = false;

    g->addPlayer("Nicolas");
    g->addPlayer("Yoan");

    for(int i = 0; i < 8; i++)
    {
        Piece &p = g->draw();
        cout << p << endl;
        cout << g->canPlace(i, 0, p) << endl;
        g->place(i, 0, p);
        DF =  t->DFS(0);
        cout << "DFS : " << DF << endl;
    }

    delete g;
}

void testCarcassonne()
{
    Game *g = new Carcassonne(0);  
    Carcassonne *t = (Carcassonne *)g;

    g->addPlayer("Yoan");
    g->addPlayer("Nicolas");

    cout << "==== First Piece drawn ====" << endl;
    Piece &p = g->draw();
    cout << p << endl;

    cout << "==== Can place at (0,1) ? ====" << endl;
    cout << boolalpha << t->canPlace(0,1,p) << endl;
    cout << "==== Place the Piece at (0,1) ====" << endl;
    // TODO : the Score hasn't changed
    cout << "==== Place a pawn ====" << endl;

    cout << "==== Can place at (0,0) ? ====" << endl;
    // TODO : Can't place here bcs there is the first piece.
    cout << boolalpha << t->canPlace(0,0,p) << endl;

    delete g;
}

/**
 * Main function for tests.
 */
int main()
{
    string request{};
    while (request.size() == 0 || request != "quit")
    {
        cout << "Enter a test" << endl;
        cin >> request;

        if (request == "dom")
            testDomPiece();
        else if (request == "trax")
            testTraxPiece();
        else if (request == "sack")
            testSack();
        else if (request == "vecz")
            testVecZ();
        else if (request == "trax1")
            testTrax_1();
        else if (request == "trax2")
            testTrax_2();
        else if (request == "carc")
            testCarcassonne();
        else if (request != "quit")
            cout << "Unknown Test. Please try again" << endl;

        cout << endl;
    }

    return EXIT_SUCCESS;
}