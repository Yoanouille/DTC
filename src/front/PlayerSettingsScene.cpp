#include "front/PlayerSettingsScene.hpp"
using namespace sf;
using namespace std;

/**
 * Constructor
 */
PlayerSettingsScene::PlayerSettingsScene(App &app, int n) : 
      app{app}, 
      nbPlayers{n}, 
      backButton{nullptr, "<", Assets::getInstance()->MainMenuFont, 200, {app.getHeight()/7.0f, app.getHeight()/7.0f}, {app.getWidth()/20.0f,app.getHeight()/23.0f}},
      plusButton{nullptr, "+", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12.0f, app.getWidth()/12.0f} , {app.getWidth()/20.0f * 17, app.getHeight()/3.8f}}, 
      minusButton{nullptr, "-", Assets::getInstance()->MainMenuFont, 100, {app.getWidth()/12.0f, app.getWidth()/12.0f}, {app.getWidth()/20.0f * 17, app.getHeight()/3.8f + app.getWidth()/12.0f + 50}},
      submitButton{nullptr, "Submit", Assets::getInstance()->MainMenuFont, 50, {app.getWidth()/6.0f, app.getHeight()/7.0f}, {app.getWidth()/2.5f, app.getHeight()/(12.0f) * 9}},
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
    float vSpace = 50.0f;
    for(int i = 1; i <= nbPlayers; i++){
      Text t{};
      t.setFont(Assets::getInstance()->MainMenuFont);
      t.setString("Player " + to_string(i));
      t.setPosition({app.getWidth()/3.5f, vSpace});
      fieldLabels.push_back(t);

      TextField tf{20, Assets::getInstance()->DefaultFont,{30,40},{app.getWidth()/3.5f, t.getPosition().y + t.getGlobalBounds().height + 20}};

      nameFields.push_back(tf);
      vSpace += tf.getPosition().y + tf.getGlobalBounds().height + 50;
    }
}

/**
 * Setup buttons' actions. (Click and Hover)
 */
void PlayerSettingsScene::initButtons(){
    // The texts turn red when the mouse hovers the button
    backButton.setActionOnMouseEntered([this](){ this->backButton.getText().setFillColor(Color::Red); });
    plusButton.setActionOnMouseEntered([this](){ this->plusButton.getText().setFillColor(Color::Red); });
    minusButton.setActionOnMouseEntered([this](){ this->minusButton.getText().setFillColor(Color::Red); });
    submitButton.setActionOnMouseEntered([this](){ this->submitButton.getText().setFillColor(Color::Red); });

    // The texts turn white when the mouse leaves the button
    backButton.setActionOnMouseExited([this](){ this->backButton.getText().setFillColor(Color::White); });
    plusButton.setActionOnMouseExited([this](){ this->plusButton.getText().setFillColor(Color::White); });
    minusButton.setActionOnMouseExited([this](){ this->minusButton.getText().setFillColor(Color::White); });
    submitButton.setActionOnMouseExited([this](){ this->submitButton.getText().setFillColor(Color::White); });

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

      // ? How To Instantiate the Game

      if(allGood){
        // Change the Scene to MainScene(id = 3)
        this->app.setScene(3);
      }
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
  while(app.pollEvent(event)){
    if (event.type == Event::Closed)
      app.close();

    Vector2f mousepos = app.mapPixelToCoords(Mouse::getPosition(app));
    for(TextField t:nameFields)
      t.handleInput(event,mousepos);

    backButton.handleHover(mousepos);
    plusButton.handleHover(mousepos);
    minusButton.handleHover(mousepos);
    submitButton.handleHover(mousepos);

    backButton.handleClick(mousepos);
    plusButton.handleClick(mousepos);
    minusButton.handleClick(mousepos);
    submitButton.handleClick(mousepos);
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
