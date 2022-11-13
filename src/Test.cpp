#include "back/DomPiece.hpp"
#include <iostream>
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
 * Main function for tests.
 */
int main()
{
    testDomPiece();
    return EXIT_SUCCESS;
}