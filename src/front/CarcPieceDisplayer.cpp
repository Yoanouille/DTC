#include "front/CarcPieceDisplayer.hpp"

CarcPieceDisplayer::CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p, Sprite& sprite) : 
    PieceDisplayer(app,x,y), piece{p}, 
    sprite{Assets::getInstance()->getCarcPiece(p.getId())}
{}

CarcPieceDisplayer::~CarcPieceDisplayer(){}

void CarcPieceDisplayer::rotate(bool clockwise) {
    piece.rotate(clockwise);
}

void CarcPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl){
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->sprite.setScale(scl,scl);

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
}
