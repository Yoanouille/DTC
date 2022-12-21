#include "front/FinalScene.hpp"
#include <iostream>
#include <string>

using namespace std;

FinalScene::FinalScene(App &a) : app{a},
        backToTitle{app, nullptr, "Back To Title", Assets::getInstance()->MainMenuFont, 58, {app.getWidth() / 4, app.getWidth() / 25}, {}},
        texts{}, mouse_coord{}
{
    init();

}

FinalScene::~FinalScene() {}

void FinalScene::init()
{
    backToTitle.setFillColor(Color::White);
    backToTitle.setPosition(app.getWidth() * 11 / 28, app.getHeight() * 6.f / 8.f);
    backToTitle.setActionOnClick([this]()
    {
        cout << "CLICKED" << endl;
        app.setScene(1, 0, nullptr);
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
    texts[0].setFillColor(Color::Magenta);
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
            texts[x].setFillColor(Color::White);
            texts[x].setFont(Assets::getInstance()->MainMenuFont);
            texts[x].setOrigin(texts[0].getGlobalBounds().width / 2, texts[0].getGlobalBounds().height / 2);
            texts[x].setPosition(app.getWidth() / 2, (x + 1) * app.getHeight() / 8);
        }
        x++;
    }
}

void FinalScene::render()
{
    app.getOldScene()->render();
    RectangleShape r{};
    r.setPosition(0,0);
    r.setSize({app.getWidth() * 1.f, app.getHeight() * 1.f});
    r.setFillColor({50,50,50,200});
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