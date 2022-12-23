#include "front/PlayerSettingsScene.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 */
PlayerSettingsScene::PlayerSettingsScene(App& app, int nbPlayers, int gamemode) : 
      app{app}, nbPlayers{nbPlayers}, 
      backButton{app, nullptr, "<", Assets::getInstance()->MainMenuFont, 200, {app.getHeight()/7.0f, app.getHeight()/7.0f}, {app.getWidth()/20.0f,app.getHeight()/23.0f}},
      gamemode{gamemode},
      plusButton{app, nullptr, "+", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12.0f, app.getWidth()/12.0f} , {app.getWidth()/20.0f * 17, app.getHeight()/3.8f}}, 
      minusButton{app, nullptr, "-", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12.0f, app.getWidth()/12.0f}, {app.getWidth()/20.0f * 17, app.getHeight()/3.8f + app.getWidth()/12.0f + 50}},
      submitButton{app, nullptr, "Submit", Assets::getInstance()->MainMenuFont, 50, {app.getWidth()/6.0f, app.getHeight()/7.0f}, {app.getWidth()/2.5f, app.getHeight()/(12.0f) * 9}},
      vSpace{50.0f}, fieldLabels{}, nameFields{},
      mousepos{}, appear{true}, disp{false}, dispF{-1}, nextScene{-1}
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
      t.setFont(Assets::getInstance()->MainMenuFont);
      t.setString("Player " + to_string(i));
      t.setPosition({app.getWidth()/3.5f, vSpace});
      t.setFillColor({255,255,255,0});
      fieldLabels.push_back(t);

      TextField tf{app, 15, Assets::getInstance()->DefaultFont,{30,40},{app.getWidth()/3.5f, t.getPosition().y + t.getGlobalBounds().height + 20}};
      nameFields.push_back(tf);
      nameFields[i - 1].setOutlineColor(Color::Cyan);
      vSpace += tf.getPosition().y + tf.getGlobalBounds().height + 50;
    }
}

/**
 * Setup buttons' actions. (Click and Hover)
 */
void PlayerSettingsScene::initButtons(){
    // The texts turn red when the mouse hovers the button
    backButton.setActionOnMouseEntered([this](){ this->backButton.fadeInColor(Color::Red); });
    plusButton.setActionOnMouseEntered([this](){ this->plusButton.fadeInColor(Color::Red); });
    minusButton.setActionOnMouseEntered([this](){ this->minusButton.fadeInColor(Color::Red); });
    submitButton.setActionOnMouseEntered([this](){ this->submitButton.fadeInColor(Color::Red); });

    // The texts turn white when the mouse leaves the button
    backButton.setActionOnMouseExited([this](){ this->backButton.fadeInColor(Color::White); });
    plusButton.setActionOnMouseExited([this](){ this->plusButton.fadeInColor(Color::White); });
    minusButton.setActionOnMouseExited([this](){ this->minusButton.fadeInColor(Color::White); });
    submitButton.setActionOnMouseExited([this](){ this->submitButton.fadeInColor(Color::White); });

    backButton.setActionOnClick([this](){ 
      this->nextScene = 1;
      this->disp = true; 
    });

    plusButton.setActionOnClick([this](){
      if(this->nbPlayers < 4)
      {
        appear = true;
        this->addPlayer();
      }
    });

    minusButton.setActionOnClick([this](){
      if(this->nbPlayers > 2)
      {
        dispF = 1;
      }
    });

    submitButton.setActionOnClick([this](){
      // Check if all the Fields are filled
      bool allGood = true;
      for (int i = 0; i < this->nbPlayers; i++){
        this->nameFields[i].trim();
        if (this->nameFields[i].getText().getString() == "") {
          this->nameFields[i].setOutlineColor(Color::Red);
          allGood = false;
        } else {
          this->nameFields[i].setOutlineColor(Color::Black);
        }
      }

      if(allGood){
        this->nextScene = 3;
        this->disp = true;
      }
    });
}

void PlayerSettingsScene::addPlayer(){
  nbPlayers++;
  Text t{};
  t.setFont(Assets::getInstance()->MainMenuFont);
  t.setString("Player " + to_string(nbPlayers));
  t.setPosition({app.getWidth()/3.5f, vSpace});
  fieldLabels.push_back(t);

  TextField tf{app, 15, Assets::getInstance()->DefaultFont,{30,40},{app.getWidth()/3.5f, t.getPosition().y + t.getGlobalBounds().height + 20}};
  nameFields.push_back(tf);

  vSpace += tf.getPosition().y + tf.getGlobalBounds().height + 50;
}

void PlayerSettingsScene::removePlayer(){
  nbPlayers--;
  vSpace -= nameFields[nameFields.size()-1].getPosition().y + nameFields[nameFields.size()-1].getGlobalBounds().height + 50; 
  fieldLabels.pop_back();
  nameFields.pop_back();
}

void PlayerSettingsScene::loop_event(){
  Event event;
  while(app.pollEvent(event)){
    if (event.type == Event::Closed)
      app.close();

    mousepos = app.mapPixelToCoords(Mouse::getPosition(app));
    if(!appear && !disp) 
    {
      for(TextField &t : nameFields)
      {
        if(Mouse::isButtonPressed(Mouse::Left) && t.contains(mousepos))
          t.setFocus(true);
        else if(Mouse::isButtonPressed(Mouse::Left))
          t.setFocus(false);
        else 
          t.handleInput(event,mousepos);
      }

      backButton.handleClick(mousepos);
      submitButton.handleClick(mousepos);

      if(gamemode != 1)
      {
        plusButton.handleClick(mousepos);
        minusButton.handleClick(mousepos);
      }

    }
  }

  if(!Mouse::isButtonPressed(Mouse::Left))
  {
    plusButton.setClicked(false);
    minusButton.setClicked(false);
  }

  if(!appear && !disp)
  {
    backButton.handleHover(mousepos);
    submitButton.handleHover(mousepos);
     if(gamemode != 1){
      plusButton.handleHover(mousepos);
      minusButton.handleHover(mousepos);
    }
  }
}

/**
 * Overriden rendering function 
 */
void PlayerSettingsScene::render(){
  if(appear)
    display();

  if(disp)
  {
    dispose();
    if(!disp && nextScene != -1){
      // Make a vector of string containing all names
      vector<string> names{};
      for (TextField t : nameFields){
          names.push_back(t.getText().getString().toAnsiString());
      }
      app.initGame(gamemode, 0);

      app.setScene(nextScene, gamemode, &names);
    } 
  }

  if(dispF != -1) 
  {
    disposeField();
    if(dispF == -1) removePlayer();
  }

  backButton.render();

  if(gamemode != 1){
    plusButton.render();
    minusButton.render();
  }
  submitButton.render();

  for(int i = 0; i < nbPlayers; i++){
    app.draw(fieldLabels[i]);
    nameFields[i].render();
  }
}

void PlayerSettingsScene::display()
{
  appear = false;
  if(!backButton.fadeIn()) appear = true;
  if(!plusButton.fadeIn()) appear = true;
  if(!minusButton.fadeIn()) appear = true;
  if(!submitButton.fadeIn()) appear = true;

  for(Text &t : fieldLabels)
  {
    Color c = t.getFillColor();
    if(c.a <= 255 - 20)
    {
      c.a += 20;
      t.setFillColor(c);
      appear = true;
    }
  }
  for(TextField &t : nameFields)
  {
    if(!t.fadeIn()) appear = true;
  }
}

void PlayerSettingsScene::dispose()
{
  disp = false;
  if(!backButton.fadeOut()) disp = true;
  if(!plusButton.fadeOut()) disp = true;
  if(!minusButton.fadeOut()) disp = true;
  if(!submitButton.fadeOut()) disp = true;

  for(Text &t : fieldLabels)
  {
    Color c = t.getFillColor();
    if(c.a >= 20)
    {
      c.a -= 20;
      t.setFillColor(c);
      disp = true;
    }
  }
  for(TextField &t : nameFields)
  {
    if(!t.fadeOut()) disp = true;
  }

}

void PlayerSettingsScene::disposeField()
{

  if(nameFields[nameFields.size()-1].fadeOut())
  {
    dispF = -1;
  } else 
  {
    Text &t = fieldLabels[fieldLabels.size() - 1];
    Color c = t.getFillColor();
    if(c.a >= 20)
    {
      c.a -= 20;
      t.setFillColor(c);
    }

  }
}