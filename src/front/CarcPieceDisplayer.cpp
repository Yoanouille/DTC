#include "front/CarcPieceDisplayer.hpp"

CarcPieceDisplayer::CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p, Sprite& sprite) : 
    PieceDisplayer(app,x,y), piece{p},
    sprite{Assets::getInstance()->CarcPieces[p.getId()]},
    dx{0}, dy{0}
{}

CarcPieceDisplayer::~CarcPieceDisplayer(){}

void CarcPieceDisplayer::rotates(bool clockwise) {
    piece.rotate(clockwise);
    
    if(clockwise){
        if((!dx && !dy) || (dx && dy)) dx = !dx;
        else if((dx && !dy) || (!dx && dy)) dy = !dy;

        this->rotate(90.0);
    }    
    else {
        if((!dx && !dy) || (dx && dy)) dy = !dy;
        else if((dx && !dy) || (!dx && dy)) dx = !dx;
        this->rotate(-90.0);
    }
}

void CarcPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl){
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->sprite.setScale(scl,scl);

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
}

void CarcPieceDisplayer::render(float x, float y, int scl){
    this->setPosition(x,y);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});

    app.draw(*this);
}
