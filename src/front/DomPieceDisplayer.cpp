#include "front/DomPieceDisplayer.hpp"

DomPieceDisplayer::DomPieceDisplayer(Menu &m, int x, int y, DomPiece &p) : PieceDisplayer{m,x,y}, piece{p} {}

DomPieceDisplayer::~DomPieceDisplayer() {}

void render()
{
}