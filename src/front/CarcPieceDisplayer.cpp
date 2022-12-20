#include "front/CarcPieceDisplayer.hpp"

CarcPieceDisplayer::CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p) : 
    PieceDisplayer(app,x,y), piece{p},
    dx{0}, dy{0}
{
    this->setTexture(&Assets::getInstance()->CarcPieceTexture);
    int startx = 16 + (p.getId() % 5) * (Assets::getInstance()->CarcPieceSize + 19);
    int starty = 15 + (p.getId() / 5) * (Assets::getInstance()->CarcPieceSize + 32);
        
    this->setTextureRect({startx,starty,Assets::getInstance()->CarcPieceSize, Assets::getInstance()->CarcPieceSize});
}

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
    this->setPosition(this->getPosition() + Vector2f{scl * dx, scl * dy});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
        app.draw(*this);
}

void CarcPieceDisplayer::render(float x, float y, int scl){
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->setPosition(x + dx * scl, y + dy * scl);
    app.draw(*this);
}

Piece &CarcPieceDisplayer::getPiece() 
{
    return piece;
}
