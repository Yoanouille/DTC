#include "back/DomPiece.hpp"

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
      tab[i][j] = rand() % 5;
}

/**
 * Find the direction on which the current Piece can be connected to a given one.
 * @param p A reference to a Piece.
 * @param pDir p's direction we are trying to connect to.
 *
 * @return An integer representing a direction (between 0 and 3) or -1 if the Pieces can't be connected.
 */
int DomPiece::connectable(Piece &p, int pDir)
{
  for (int dir = 0; dir < 4; dir++)
    if (tab[dir] == ((DomPiece &)p).tab[pDir])
      return dir;
  return -1;
}

/**
 * Computes the earnable value if we manage to connect the current Piece to the given Piece.
 *
 * @param p A reference to a Piece
 * @param pDir The side of p on which we connect the current Piece.
 *
 * @return the maximum value
 */
int DomPiece::getEarnedValue(Piece &p, int pDir)
{
  int dir = connectable(p, pDir);
  if (dir == -1)
    return 0;

  int sum = 0;
  for (size_t i = 0; i < 3; i++)
    sum += ((DomPiece &)p).tab[pDir][i];
  return sum;
}
