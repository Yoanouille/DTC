#include "back/DomPiece.hpp"
using namespace std;

/**
 * Constructor
 *
 * allocates an array of array with size 4*3
 * fills it with random values from 0 to 4
 * (The random generation may be changed in a near future).
 */
DomPiece::DomPiece() : tab{}
{
  for (size_t i = 0; i < 4; i++)
    for (size_t j = 0; j < 3; j++)
      tab[i][j] = rand() % 2;
}

/** Destructor */
DomPiece::~DomPiece() {}

/**
 * Test if the current Piece can be connected to a given one.
 * @param p A reference to a Piece.
 * @param pDir p's direction we are trying to connect to.
 * @param dir the current Piece's direction we want to connect on p.
 *
 * @return A boolean
 */
bool DomPiece::connectable(Piece &p, int pDir)
{
  int count = 0;
  for (int j = 0; j < 3; j++)
    if (tab[(pDir + direction + 2)%4][2 - j] == ((DomPiece &)p).tab[((pDir + ((DomPiece &)p).direction)) % 4][j])
      count ++;
  return (count >= 1);
}

/**
 * Computes the earnable value if we manage to connect the current Piece to the given Piece.
 *
 * @param p A reference to a Piece
 * @param pDir The side of p on which we connect the current Piece.
 *
 * @return The earnable value
 */
int DomPiece::getEarnedValue(Piece &p, int pDir)
{
  int sum = 0;
  for (int j = 0; j < 3; j++)
  {
    if (tab[(pDir + direction + 2)%4][2 - j] == ((DomPiece &)p).tab[((pDir + ((DomPiece &)p).direction)) % 4][j])
    {
      sum += tab[(pDir + direction + 2)%4][2 - j];
    }
  }
  return sum;
}

/**
 * Create a String for printing.
 * It will generate the following string
 * ---- DomPiece ----
 *  a b c
 * d     g
 * e     h
 * f     i
 *  j k l
 */
string DomPiece::toString() const
{
  string s{" "};
  for (size_t j = 0; j < 3; j++)
    s += to_string(tab[0][j]) + " ";
  s += "\n";

  for (size_t j = 0; j < 3; j++)
    s += to_string(tab[1][2 - j]) + "     " + to_string(tab[3][j]) + "\n";
  s += " ";
  for (size_t j = 0; j < 3; j++)
    s += to_string(tab[2][2 - j]) + " ";

  return s;
}

int DomPiece::getVal(int dir, int i)
{
  return tab[(dir + direction)%4][i];
}