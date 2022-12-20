#include "front/DomPieceDisplayer.hpp"
#include "front/AssetsLoader.hpp"

using namespace sf;

DomPieceDisplayer::DomPieceDisplayer(App &app, int x, int y, DomPiece &p) : PieceDisplayer{app,x,y}, piece{p}, rect{}, text{}
{   
    Color c{255,255,255,255};
    this->setFillColor(c);
    this->setOutlineColor(Color::Transparent);


    text.setFont(Assets::getInstance()->DefaultFont);
    text.setFillColor({255,0,0,255});

    rect.setPosition(-20,-20);
    rect.setFillColor(Color::Transparent);
    rect.setOutlineThickness(0);
    rect.setOutlineColor({0,0,0,0});
}

DomPieceDisplayer::~DomPieceDisplayer() {}


void DomPieceDisplayer::render(sf::Vector2f &off, sf::RectangleShape &board, int scl, sf::Vector2f &mouse)
{
    Vector2f v{static_cast<float>(coordinates.x * scl), static_cast<float>(coordinates.y * scl)};
    Vector2f dp{3.0,3.0};
    this->setPosition(v + board.getPosition() + off + dp);
    this->setSize({static_cast<float>(scl - dp.x), static_cast<float>(scl - dp.y)});
    this->setOutlineColor({0,0,0,255});
    this->setOutlineThickness(3);

    if (this->getGlobalBounds().intersects(board.getGlobalBounds()))
    {
        app.draw(*this);
        drawRect(scl);
    }
}

void DomPieceDisplayer::render(float x, float y, int scl)
{
    Vector2f dp{3.0,3.0};
    this->setPosition(x, y);
    this->setSize({static_cast<float>(scl - dp.x), static_cast<float>(scl - dp.y)});
    this->setOutlineColor({0,0,0,255});
    this->setOutlineThickness(3);

    app.draw(*this);
    drawRect(scl);
}

void DomPieceDisplayer::drawRect(int s)
{
    Vector2f dp{1,1};
    s -= 3.0;
    float scl = s / 5.0;
    rect.setSize({scl - dp.x * 0.5f, scl - dp.y * 0.5f});
    rect.setOutlineThickness(1);
    rect.setOutlineColor({0,0,0,255});
    app.draw(rect);  

    text.setCharacterSize(scl);
    text.setString("0");
    FloatRect r = text.getGlobalBounds();
    // text.setOrigin(0.5 * r.width, 0.5 * r.height);
    

    float x = this->getPosition().x;
    float y = this->getPosition().y;
    for(int i = 0; i < 5; i++)
    {
        if(i == 0 || i == 4)
            rect.setFillColor({50,50,50,255});
        else
            rect.setFillColor(Color::White);

        rect.setPosition({x + i * scl + dp.x, y + dp.y});
        app.draw(rect);

        if(i != 0)
        {
            rect.setPosition({x + dp.x, y + i * scl + dp.y});
            app.draw(rect);
        }

        rect.setPosition({x + i * scl + dp.x, y + 4 * scl + dp.y});
        app.draw(rect);

        if(i != 4)
        {
            rect.setPosition({x + 4 * scl + dp.x, y + i * scl + dp.y});
            app.draw(rect);
        }

        if(i >= 1 && i <= 3)
        {
            text.setPosition({x + i * scl + dp.x + r.width * 0.5f, y + dp.y - r.height * 0.20f});
            text.setString(to_string(piece.getVal(Direction::UP, i - 1)));
            app.draw(text);

            text.setPosition({x + i * scl + dp.x + r.width * 0.5f, y  + 4 * scl + dp.y - r.height * 0.20f});
            text.setString(to_string(piece.getVal(Direction::DOWN, 3 - i)));
            app.draw(text);  

            text.setPosition({x + dp.x + r.width * 0.5f, y  + i * scl + dp.y - r.height * 0.20f});
            text.setString(to_string(piece.getVal(Direction::LEFT, 3 - i)));
            app.draw(text);

            text.setPosition({x + 4.0f * scl + dp.x + r.width * 0.5f, y  + i * scl + dp.y - r.height * 0.20f});
            text.setString(to_string(piece.getVal(Direction::RIGHT, i - 1)));
            app.draw(text);          
        }
    }

    rect.setFillColor(Color::Transparent);
    rect.setOutlineThickness(0);

}

void DomPieceDisplayer::rotates(bool clockwise)
{
    piece.rotate(clockwise);
}

Piece &DomPieceDisplayer::getPiece()
{
    return piece;
}