#include "front/FinalScene.hpp"
#include <iostream>
#include <string>

using namespace std;

FinalScene::FinalScene(App &a) : app{a},
        backToTitle{app, nullptr, "Back To Title", Assets::getInstance()->MainMenuFont, 58, {app.getWidth() / 4, app.getWidth() / 25}, {}},
        texts{}, mouse_coord{}, r{}, appear{true}, disp{false}, disp2{false}
{
    init();

}

FinalScene::~FinalScene() {}

void FinalScene::init()
{
    r.setPosition(0,0);
    r.setSize({app.getWidth() * 1.f, app.getHeight() * 1.f});
    r.setFillColor({50,50,50,0});
    
    //backToTitle.setFillColor(Color::White);
    backToTitle.setPosition(app.getWidth() * 11 / 28, app.getHeight() * 6.f / 8.f);
    backToTitle.setActionOnClick([this]()
    {
        disp = true;
    });

    backToTitle.setActionOnMouseEntered([this]()
    {
        this->backToTitle.fadeInColor(Color::Red);
    });

     backToTitle.setActionOnMouseExited([this]()
    {
        this->backToTitle.fadeInColor(Color::White);
    });

    Player *p = app.getGame()->getWinner();

    texts.push_back({});
    texts[0].setString("Le Gagnant est :" + p->getName() + " !!!!");
    texts[0].setCharacterSize(58);
    Color c = Color::Magenta;
    c.a = 0;
    texts[0].setFillColor(c);
    texts[0].setFont(Assets::getInstance()->MainMenuFont);
    texts[0].setOrigin(texts[0].getGlobalBounds().width / 2, texts[0].getGlobalBounds().height / 2);
    texts[0].setPosition(app.getWidth() / 2, app.getHeight() / 8);
    for(size_t i = 0; i < app.getGame()->getPlayers().size(); i++)
    {
        int x = 1;
        if(app.getGame()->getPlayers()[i] != p)
        {
            texts.push_back({});
            texts[x].setString(app.getGame()->getPlayers()[i]->getName() + " : " + to_string(app.getGame()->getPlayers()[i]->getScore()));
            texts[x].setCharacterSize(48);
            texts[x].setFillColor({255,255,255,0});      
            texts[x].setFont(Assets::getInstance()->MainMenuFont);
            texts[x].setOrigin(texts[0].getGlobalBounds().width / 2, texts[0].getGlobalBounds().height / 2);
            texts[x].setPosition(app.getWidth() / 2, (x + 1) * app.getHeight() / 8);
        }
        x++;
    }
}

void FinalScene::render()
{
    if(!disp2) app.getOldScene()->render();
    if(appear) display();
    if(disp)
    {
        dispose();
        if(!disp) app.setScene(1, 0, nullptr);
    }
    
    app.draw(r);
    backToTitle.render();

    for(Text &t : texts)
    {
        app.draw(t);
    }

}

void FinalScene::loop_event()
{
    Event event;
    while(app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.close();
        
        mouse_coord = app.mapPixelToCoords(Mouse::getPosition(app));


        
    }

    backToTitle.handleHover(mouse_coord);
    backToTitle.handleClick(mouse_coord);
}

void FinalScene::display()
{
    bool flag = false;
    Color c = r.getFillColor();
    if(c.a < 200 - 2)
    {
        c.a += 2;
        flag = true;
        r.setFillColor(c);
    }
    if(!backToTitle.fadeIn()) flag = true;
    for(Text &t : texts)
    {
        c = t.getFillColor();
        if(c.a <= 255 - 5)
        {
            c.a += 5;
            flag = true;
        }
        t.setFillColor(c);
    }
    appear = flag;
}

void FinalScene::dispose()
{

    bool flag = false;
    Color c = r.getFillColor();
    if(!disp2 && c.a < 254)
    {
        c.a += 1;
        flag = true;
        r.setFillColor(c);
        return;
    }
    disp2 = true;
    if(c.a > 2)
    {
        c.a -= 2;
        flag = true;
        r.setFillColor(c);
    }
    if(!backToTitle.fadeOut()) flag = true;
    for(Text &t : texts)
    {
        c = t.getFillColor();
        if(c.a > 5)
        {
            c.a -= 5;
            flag = true;
            t.setFillColor(c);
        }
    }
    disp = flag;

}