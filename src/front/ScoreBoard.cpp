#include "front/ScoreBoard.hpp"

/**
 * Constructor 
 */
ScoreBoard::ScoreBoard(App &app) : app{app}, game{nullptr}, container{}, appear{true}
{
    // Setup the container
    container.setSize(Vector2f(app.getWidth() / 6.0f, (app.getHeight() / 3.0f)));
    container.setPosition(Vector2f((app.getWidth() * 10.0) / 5.0f, app.getHeight() * -10.f /20.0f));
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
        names[i].setCharacterSize(20);
        names[i].setPosition({container.getPosition().x + container.getSize().x / 8.0f, vspace });

        scores.push_back({});
        scores[i].setString(to_string(game->getPlayers()[i]->getScore()));
        scores[i].setFillColor(Color::Black);
        scores[i].setFont(Assets::getInstance()->DefaultFont);
        scores[i].setCharacterSize(20);
        scores[i].setPosition({container.getPosition().x + container.getSize().x * 0.75f, vspace });

        if (app.getGamemode() == CARCASSONNE){
            scores[i].setPosition({container.getPosition().x + container.getSize().x * 0.60f, vspace });

            nbPawns.push_back({});
            nbPawns[i].setString(to_string(((PlayerCarc *)(game->getPlayers()[i]))->getNbPawn()));
            nbPawns[i].setFillColor(Color::Black);
            nbPawns[i].setFont(Assets::getInstance()->DefaultFont);
            nbPawns[i].setCharacterSize(20);
            nbPawns[i].setPosition({container.getPosition().x + container.getSize().x * 0.80f, vspace });
        }
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

    if(app.getGamemode() == CARCASSONNE){
        for(size_t i = 0; i < game->getPlayers().size(); i++)
            nbPawns[i].setString(to_string(((PlayerCarc *)(game->getPlayers()[i]))->getNbPawn()));
    }
}

/**
 * Rendering function 
 */
void ScoreBoard::render(){
    app.draw(container);

    if(appear) display();
    // Draw the text
    for(size_t i = 0; i < names.size() ; i++){
        app.draw(names[i]);
        app.draw(scores[i]);

        if(app.getGamemode() == CARCASSONNE)
            app.draw(nbPawns[i]);
    }
}

void ScoreBoard::display()
{
    float x = container.getPosition().x;
    float y = container.getPosition().y;
    bool flag = false; 
    if(x > (app.getWidth() * 4.0) / 5.0f) 
    {
        x -= (app.getWidth() * 4.0) / (5.0f * 200.f);
        flag = true;
    } else x = (app.getWidth() * 4.0) / 5.0f;
    if(y < (app.getHeight()) / 20.0f) 
    {
        y +=  app.getHeight()/(20.0f * 20.f);
        flag = true;
    } else y = app.getHeight() / 20.0f;
    appear = flag;

    container.setPosition(x,y);
    float vspace = container.getSize().y / 10.0f;
    for(size_t i = 0; i< game->getPlayers().size() ; i++)
    {
        names[i].setPosition({container.getPosition().x + container.getSize().x / 8.0f, vspace + y });
        scores[i].setPosition({container.getPosition().x + container.getSize().x * 0.75f, vspace  + y});
        if (app.getGamemode() == CARCASSONNE)
        {
            scores[i].setPosition({container.getPosition().x + container.getSize().x * 0.60f, vspace + y});
            nbPawns[i].setPosition({container.getPosition().x + container.getSize().x * 0.80f, vspace + y});
        }
        vspace += container.getSize().y / 5.0f;
    }

}