#include "front/PieceDisplayer.hpp"
using namespace sf;

PieceDisplayer::PieceDisplayer(App &app, int x, int y) : app{app}, coordinates{x, y} {}

PieceDisplayer::~PieceDisplayer() {}
