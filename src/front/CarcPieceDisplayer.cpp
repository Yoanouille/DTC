#include "front/CarcPieceDisplayer.hpp"
#include "back/PlayerCarc.hpp"

CarcPieceDisplayer::CarcPieceDisplayer(App& app, int x, int y, CarcPiece &p) : 
    PieceDisplayer(app,x,y), piece{p},
    dx{0}, dy{0}, rect{}
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

void CarcPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse){
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    this->setPosition(v + board.getPosition() + off);
    this->setSize({static_cast<float>(scl), static_cast<float>(scl)});
    this->setPosition(this->getPosition() + Vector2f{scl * dx, scl * dy});

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
    {
        app.draw(*this);
        if(state == 1) drawRect(mouse, scl);
        else if(state == 2) drawPawn(scl);
    }


}

void CarcPieceDisplayer::drawPawn(int s)
{
    float scl = s / 5.0;
    rect.setSize({scl / 2.0, scl / 2.0});
    if(!piece.hasPawn()) return;
    Pos p = piece.getPosPawn();

    float x = this->getPosition().x - s * dx;
    float y = this->getPosition().y - s * dy;
    if(p.i == UP)
    {
        rect.setFillColor(Color::Red);
        rect.setPosition(x + scl * (p.j + 1) + scl / 4.0, y + scl / 4.0);
        app.draw(rect);
    }
    if(p.i == DOWN)
    {
        rect.setFillColor(Color::Red);
        rect.setPosition(x + scl * (3 - p.j) + scl / 4.0, y + scl * 4 + scl / 4.0);
        app.draw(rect);
    }
    if(p.i == LEFT)
    {
        rect.setFillColor(Color::Red);
        rect.setPosition(x + scl / 4.0, y + (3 - p.j) * scl + scl / 4.0);
        app.draw(rect);
    }
    if(p.i == RIGHT)
    {
        rect.setFillColor(Color::Red);
        rect.setPosition(x + 4 * scl + scl / 4.0, y +  (p.j + 1) * scl + scl / 4.0);
        app.draw(rect);
    }
}

void CarcPieceDisplayer::drawRect(Vector2f &mouse, int s)
{
    Vector2f dp{1,1};
    s -= 3.0;
    float scl = s / 5.0;
    rect.setSize({scl - dp.x * 0.5f, scl - dp.y * 0.5f});
    rect.setOutlineThickness(0);
    rect.setOutlineColor({0,0,0,0});
    app.draw(rect);  
    
    float x = this->getPosition().x - s * dx;
    float y = this->getPosition().y - s * dy;
    for(int i = 1; i < 4; i++)
    {

        rect.setPosition({x + i * scl + dp.x, y + dp.y});
        if(rect.getGlobalBounds().contains(mouse)) rect.setFillColor({0,0,255,255});
        else rect.setFillColor({0,0,255,100});
        app.draw(rect);

        rect.setPosition({x + dp.x, y + i * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse)) rect.setFillColor({0,0,255,255});
        else rect.setFillColor({0,0,255,100});
        app.draw(rect);

        rect.setPosition({x + i * scl + dp.x, y + 4 * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse)) rect.setFillColor({0,0,255,255});
        else rect.setFillColor({0,0,255,100});
        app.draw(rect);
        
        rect.setPosition({x + 4 * scl + dp.x, y + i * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse)) rect.setFillColor({0,0,255,255});
        else rect.setFillColor({0,0,255,100});
        app.draw(rect);
        
    }

    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor({0,0,0,0});
    rect.setOutlineThickness(0);

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

void CarcPieceDisplayer::nextState()
{
    if(state < 2) state++;
}

bool CarcPieceDisplayer::isFinalState()
{
    return (state == 2);
}

void CarcPieceDisplayer::handleClick(sf::Vector2f &mouse, Player *p, int player, int s) 
{
    //TODO Vérifier qu'il peut poser le pion
    if(!this->getGlobalBounds().contains(mouse)) return;

    PlayerCarc *pl = (PlayerCarc *)(p);
    if(pl->getNbPawn() == 0) return; 

    Vector2f dp{1,1};
    s -= 3.0;
    float scl = s / 5.0;
    rect.setSize({scl - dp.x * 0.5f, scl - dp.y * 0.5f});
    rect.setOutlineThickness(0);
    rect.setOutlineColor({0,0,0,0});
    app.draw(rect);  
    
    float x = this->getPosition().x - s * dx;
    float y = this->getPosition().y - s * dy;
    for(int i = 1; i < 4; i++)
    {
       
        rect.setFillColor({0,0,255,100});

        rect.setPosition({x + i * scl + dp.x, y + dp.y});
        if(rect.getGlobalBounds().contains(mouse)) 
        {
            piece.putPawn(Direction::UP, i - 1, false, player);
            piece.printColor();
            pl->addPawn(-1);
            return;
        }

        rect.setPosition({x + i * scl + dp.x, y + 4 * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse))
        {
            piece.putPawn(Direction::DOWN, 3 - i, false, player);
            pl->addPawn(-1);
            piece.printColor();

            return;
        }

        rect.setPosition({x + dp.x, y + i * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse))
        {
            piece.putPawn(Direction::LEFT, 3 - i, false, player);
            piece.printColor();
            pl->addPawn(-1);

            return;
        }
        
        rect.setPosition({x + 4 * scl + dp.x, y + i * scl + dp.y});
        if(rect.getGlobalBounds().contains(mouse))
        {
            piece.putPawn(Direction::RIGHT, i - 1, false, player);
            piece.printColor();
            pl->addPawn(-1);

            return;
        }
    }

}

void CarcPieceDisplayer::removeHandle(Player *p, int player) 
{
    if(piece.hasPawn()) ((PlayerCarc *)p)->addPawn(1);
    piece.removeALLPawn();

}
