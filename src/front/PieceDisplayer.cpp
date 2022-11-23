#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(Menu &m, int x, int y) : menu{m}, coordinates{x, y} {}

PieceDisplayer::~PieceDisplayer() {}