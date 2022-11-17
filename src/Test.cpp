#include "back/DomPiece.hpp"
#include "back/TraxPiece.hpp"
#include "back/Sack.hpp"

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
    cout << "==== Connectable on Dom2 ====" << endl;
    for (int i = 0; i < 4; i++)
        cout << "Direction " << i << ":" << dom1.connectable((Piece &)dom2, i) << endl;

    // 3
    cout << "==== getEarnedValue on Dom2 ====" << endl;
    for (int i = 0; i < 4; i++)
        cout << "Direction " << i << ":" << dom1.getEarnedValue((Piece &)dom2, i) << endl;
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
 */
void testSack()
{
    Sack domSack{5, 0};
    Sack traxSack{5, 1};

    cout << "---- DomPieces ----" << endl;
    cout << domSack << endl;
    cout << "---- TraxPieces ----" << endl;
    cout << traxSack << endl;

    cout << "==== Unknwown Gamemode Test" << endl;
    try
    {
        Sack unknown{5, 3};
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
        else if (request != "quit")
            cout << "Unknown Test. Please try again" << endl;

        cout << endl;
    }

    return EXIT_SUCCESS;
}