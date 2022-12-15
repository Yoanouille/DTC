#include "front/DrawZone.hpp"

#include "front/DomPieceDisplayer.hpp"
#include "front/TraxPieceDisplayer.hpp"
#include "front/CarcPieceDisplayer.hpp"

/**
 * Constructor 
 * Rotate right Button need some transformations.
 */
DrawZone::DrawZone(App &app, bool isTraxGame): 
    app{app}, isTraxGame{isTraxGame},
    container{Vector2f(app.getWidth() / 6.0f, (app.getHeight() / 2.0f))},
    sack{app, &Assets::getInstance()->Sack,"", Assets::getInstance()->DefaultFont, 0, {container.getSize().x / 3.0f, container.getSize().x/3.0f}, {}},
    r{Vector2f(container.getSize().x / 1.35f , container.getSize().x / 1.35f )},
    pieceViewer{nullptr},
    rotateLeft{app, &Assets::getInstance()->RotateLeft, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f}, {}},
    rotateRight{app, &Assets::getInstance()->RotateLeft, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f}, {}},
    flipButton{app, &Assets::getInstance()->Flip, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f},{}}
{
    container.setPosition(Vector2f((app.getWidth() * 4.0f) / 5.0f, app.getHeight() * 0.45f));
    container.setFillColor(Color::White);

    r.setFillColor(Color::Black);
    r.setPosition(container.getPosition().x + container.getSize().x *0.5f - r.getGlobalBounds().width * 0.5f, container.getPosition().y + container.getSize().x * 0.45f);

    rotateLeft.setPosition(container.getPosition().x + rotateLeft.getGlobalBounds().width *0.2f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);

    rotateRight.setPosition(container.getPosition().x + container.getSize().x - rotateRight.getGlobalBounds().width * 1.05f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);
    Sprite *sp = rotateRight.getSprite();
    sp->setScale(-sp->getScale().x, sp->getScale().y);
    sp->setPosition(rotateRight.getPosition().x + rotateRight.getGlobalBounds().width * 0.85f, rotateRight.getPosition().y);

    sack.setPosition(container.getPosition().x + container.getSize().x * 0.5f - sack.getGlobalBounds().width *0.5f , container.getPosition().y + container.getGlobalBounds().height - sack.getGlobalBounds().height * 1.02f);

    // Setup buttons
    sack.setActionOnClick([this]{
        this->draw();    
    });

    rotateLeft.setActionOnClick([this]{
        if(this->getPieceViewer() != nullptr)
            this->getPieceViewer()->rotates(false);
    });

    rotateRight.setActionOnClick([this]{
        if(this->getPieceViewer() != nullptr)
            this->getPieceViewer()->rotates(true);
    });

    if(isTraxGame)
    {
        flipButton.setPosition(rotateRight.getPosition().x - flipButton.getGlobalBounds().width*1.05f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);
        flipButton.setActionOnClick([this]{
            if(this->getPieceViewer() != nullptr)
                ((TraxPieceDisplayer *)(this->getPieceViewer()))->flip();
        });
    }
}

DrawZone::~DrawZone()
{
    if(pieceViewer != nullptr) delete pieceViewer;
}

/**
 * Rendering function 
 */
void DrawZone::render(){
    app.draw(container);
    sack.render();

    if(pieceViewer != nullptr)
        pieceViewer->render(r.getPosition().x, r.getPosition().y, r.getSize().x);
    else 
        app.draw(r);
        
    rotateLeft.render();
    rotateRight.render();
    if(isTraxGame) flipButton.render();
}

App &DrawZone::getApp(){
    return app;
}

PieceDisplayer *DrawZone::getPieceViewer(){
    return pieceViewer;
}

void DrawZone::draw(){
    Piece &p = app.getGame()->draw();
    switch(app.getGamemode()){
        case 0 :
            pieceViewer = new DomPieceDisplayer(app, 0, 0, (DomPiece&)(p));
            break;

        case 1 :
            pieceViewer = new TraxPieceDisplayer(app, 0, 0, (TraxPiece&)(p));
            break;

        case 2 :
            pieceViewer = new CarcPieceDisplayer(app, 0, 0, (CarcPiece&)(p));
            break;

        default :
            throw UnknownGamemodeException();
            break;
    }
    
}

PieceDisplayer *DrawZone::pick()
{
    PieceDisplayer *p = pieceViewer;
    pieceViewer = nullptr;
    return p;
}