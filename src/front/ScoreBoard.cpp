#include "front/ScoreBoard.hpp"

/**
 * Constructor 
 */
ScoreBoard::ScoreBoard(App &app) : app{app}, game{nullptr}, container{}
{
    // Setup the container
    container.setSize(Vector2f(app.getWidth() / 6.0f, (app.getHeight() / 3.0f)));
    container.setPosition(Vector2f((app.getWidth() * 4.0) / 5.0f, app.getHeight()/20.0f));
    container.setFillColor(Color::White);

    // The texts are initialized in setGame()
}

ScoreBoard::~ScoreBoard(){}

/**
 * Size getter
 * @return A Vector2f containing the size 
 */
sf::Vector2f ScoreBoard::getSize(){
    return container.getSize();
}

/**
 * Position getter
*/
sf::Vector2f ScoreBoard::getPosition() const{
    return container.getPosition();
}

void ScoreBoard::setPosition(sf::Vector2f pos){
    container.setPosition(pos);
}

/**
 * Game setter
 * 
 * Called once the game has been initialized.
 * This function initializes all the texts.
 */
void ScoreBoard::setGame(Game *game){
    this->game = game;

     // Setup the text
    float vspace = container.getSize().y / 5.0f;
    for(size_t i = 0; i< game->getPlayers().size() ; i++){
        names.push_back({});
        names[i].setString(game->getPlayers()[i]->getName());
        if(i == 0) names[i].setFillColor(Color::Cyan);
        else names[i].setFillColor(Color::Black);
        names[i].setFont(Assets::getInstance()->DefaultFont);
        names[i].setCharacterSize(30);
        names[i].setPosition({container.getPosition().x + container.getSize().x / 8.0f, vspace });

        scores.push_back({});
        scores[i].setString(to_string(game->getPlayers()[i]->getScore()));
        scores[i].setFillColor(Color::Black);
        scores[i].setFont(Assets::getInstance()->DefaultFont);
        scores[i].setPosition({container.getPosition().x + container.getSize().x * 0.75f, vspace });

        vspace += container.getSize().y / 5.0f;
    }
}

/**
 * Update method 
 */
void ScoreBoard::update(){
    for(size_t i = 0; i < game->getPlayers().size(); i++)
        scores[i].setString(to_string(game->getPlayers()[i]->getScore()));
    for(size_t i = 0; i < game->getPlayers().size(); i++)
        names[i].setFillColor(Color::Black);
    names[game->getCurrentPlayer()].setFillColor(Color::Cyan);
}

/**
 * Rendering function 
 */
void ScoreBoard::render(){
    app.draw(container);

    // Draw the text
    for(size_t i = 0; i < names.size() ; i++){
        app.draw(names[i]);
        app.draw(scores[i]);
    }
}