#include "front/DomPieceDisplayer.hpp"

DomPieceDisplayer::DomPieceDisplayer(Menu &m, DomPiece &p) : PieceDisplayer(m), piece{&p} {}

DomPieceDisplayer::~DomPieceDisplayer() {}

void render()
{
}