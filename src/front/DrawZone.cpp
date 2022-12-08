#include "front/DrawZone.hpp"

/**
 * Constructor 
 * Rotate right Button need some transformations.
 */
DrawZone::DrawZone(App &app, bool isTraxGame): 
    app{app}, isTraxGame{isTraxGame},
    container{Vector2f(app.getWidth() / 6.0f, (app.getHeight() / 2.0f))},
    sack{app, &Assets::getInstance()->Sack,"", Assets::getInstance()->DefaultFont, 0, {container.getSize().x / 3.0f, container.getSize().x/3.0f}, {}},
    pieceViewer{Vector2f(container.getSize().x / 1.35f , container.getSize().x / 1.35f )},
    rotateLeft{app, &Assets::getInstance()->RotateLeft, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f}, {}},
    rotateRight{app, &Assets::getInstance()->RotateLeft, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f}, {}},
    flipButton{app, &Assets::getInstance()->Flip, "", Assets::getInstance()->DefaultFont, 0, {container.getSize().x/4.0f, container.getSize().x/4.0f},{}}
{
    container.setPosition(Vector2f((app.getWidth() * 4.0f) / 5.0f, app.getHeight() * 0.45f));
    container.setFillColor(Color::White);

    pieceViewer.setFillColor(Color::Black);
    pieceViewer.setPosition(container.getPosition().x + container.getSize().x *0.5f - pieceViewer.getGlobalBounds().width * 0.5f, container.getPosition().y + container.getSize().x * 0.45f);

    rotateLeft.setPosition(container.getPosition().x + rotateLeft.getGlobalBounds().width *0.2f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);

    rotateRight.setPosition(container.getPosition().x + container.getSize().x - rotateRight.getGlobalBounds().width * 1.05f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);
    Sprite *sp = rotateRight.getSprite();
    sp->setScale(-sp->getScale().x, sp->getScale().y);
    sp->setPosition(rotateRight.getPosition().x + rotateRight.getGlobalBounds().width * 0.85f, rotateRight.getPosition().y);

    flipButton.setPosition(rotateRight.getPosition().x - flipButton.getGlobalBounds().width*1.05f, container.getPosition().y + rotateLeft.getGlobalBounds().height * 0.2f);

    sack.setPosition(container.getPosition().x + container.getSize().x * 0.5f - sack.getGlobalBounds().width *0.5f , container.getPosition().y + container.getGlobalBounds().height - sack.getGlobalBounds().height * 1.02f);
}

DrawZone::~DrawZone(){}

/**
 * Rendering function 
 */void DrawZone::render(){
    app.draw(container);
    sack.render();
    app.draw(pieceViewer);
    rotateLeft.render();
    rotateRight.render();
    if(isTraxGame) flipButton.render();
}