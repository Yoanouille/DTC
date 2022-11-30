#include "front/PlayerSettingsScene.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 */
PlayerSettingsScene::PlayerSettingsScene(App &app, int n) : 
      app{app}, 
      nbPlayers{n}, 
      backButton{nullptr, "<", Assets::getInstance()->MainMenuFont, 200, {app.getWidth()/5, app.getHeight()/6}, {0,0}},
      plusButton{nullptr, "+", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12,app.getWidth()/12}, {0,300}}, 
      minusButton{nullptr, "-", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12,app.getWidth()/12}, {170,300}},
      submitButton{nullptr, "Submit", Assets::getInstance()->MainMenuFont, 50, {app.getWidth()/5, app.getHeight()/6}, {400,300}},
      fieldLabels{}, nameFields{}
{ 
  initFields(); 
  initButtons();
}

PlayerSettingsScene::~PlayerSettingsScene(){}

/**
 * Setup TextFields and Labels
 */
void PlayerSettingsScene::initFields(){
    for(int i = 1; i <= nbPlayers; i++){
      Text t{};
      t.setString("Player " + to_string(i));
      fieldLabels.push_back(t);
      nameFields.push_back({20, Assets::getInstance()->DefaultFont,{3,20},{560,40}});
      // TODO : place the fields better.
    }
}

/**
 * Setup buttons' actions. 
 */
void PlayerSettingsScene::initButtons(){
    backButton.setActionOnClick([this](){ 
      this->app.setScene(2);
    });

    plusButton.setActionOnClick([this](){
      if(this->nbPlayers < 4)
        this->addPlayer();
    });

    minusButton.setActionOnClick([this](){
      if(this->nbPlayers > 1)
        this->removePlayer();
    });

    submitButton.setActionOnClick([this](){
      // TODO : Check if all the Fields are filled
      // TODO : Instantiate the Game

      // Change the Scene to MainScene(id = 3)
      this->app.setScene(3);
    });
}

void PlayerSettingsScene::addPlayer(){
  nbPlayers++;
  Text t{};
  t.setString("Player " + to_string(nbPlayers));
  fieldLabels.push_back(t);
  nameFields.push_back({20, Assets::getInstance()->DefaultFont,{3,20}, {560,80}});
}

void PlayerSettingsScene::removePlayer(){
  nbPlayers--;
  fieldLabels.pop_back();
  nameFields.pop_back();
}

void PlayerSettingsScene::loop_event(){
  Event event;
  while(!app.pollEvent(event)){
    if (event.type == Event::Closed)
      app.close();
    for(TextField t:nameFields)
      t.handleInput(event);

    Vector2f mousepos = app.mapPixelToCoords(Mouse::getPosition(app));

    backButton.handleClick(event,mousepos);
    plusButton.handleClick(event,mousepos);
    minusButton.handleClick(event,mousepos);
    submitButton.handleClick(event,mousepos);
  }
}

/**
 * Overriden rendering function 
 */
void PlayerSettingsScene::render(){
  backButton.render(app);
  plusButton.render(app);
  minusButton.render(app);
  submitButton.render(app);

  for(int i = 0; i < nbPlayers; i++){
    app.draw(fieldLabels[i]);
    nameFields[i].render(app);
  }
}
