#include "front/MainScene.hpp"
#include "front/TraxPieceDisplayer.hpp"
#include "front/DomPieceDisplayer.hpp"
#include "back/Domino.hpp"
#include "front/AssetsLoader.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 * Initialize some variables, call init()
 */
MainScene::MainScene() : 
    scoreBoard{}, board{}, scl{75}, off{180, 180}, 
    rect{}, rectBG{}, pos_mouse{0, 0}, mouse_coord{0, 0}, 
    pos{}, right_pressed{false}, left_pressed{false}, old_pos{0, 0}, 
    disp{false}, appear{true}, speed1{40}, speed2{3}
{
    //TODO depend du jeu ! donc arguments au constructeur !
    game = new Domino();
    init();
}

/**
 * Destructor
 */
MainScene::~MainScene() 
{
    if(game != nullptr) delete game;
}

/**
 * initialize the scene
 */
void MainScene::init()
{
    // setup the scoreboard
    scoreBoard.setSize(Vector2f(App::getInstance()->getWidth() / 5, App::getInstance()->getHeight()));
    scoreBoard.setPosition(Vector2f((App::getInstance()->getWidth() * 6.0) / 5, 0));
    scoreBoard.setFillColor(Color::White);

    // setup the board
    double dx = (App::getInstance()->getWidth() - scoreBoard.getSize().x);
    board.setSize(Vector2f(dx * 15.0 / 16, App::getInstance()->getHeight() * 17 / 18));
    board.setPosition(Vector2f(App::getInstance()->getWidth() / 32.0, App::getInstance()->getHeight() * 38.0 / 36));
    // RGBA format
    Color c{0, 0, 0, 200};
    board.setFillColor(c);

    rectBG.setTexture(&Assets::getInstance()->MainMenuBackground);
    rectBG.setScale(0.33, 0.33);


    // Set up controller
    // Controller & controller = (Controller::getInstance());
    // controller.bindActionOnKey(Keyboard::Left, [this](){ 
    //     for(PieceDisplayer * p : this->pos){
    //         p->rotate(true);
    //     }
    // });

    // controller.bindActionOnKey(Keyboard::Right, [this](){
    //     for(PieceDisplayer * p : this->pos){
    //         p->rotate(true);
    //     }
    // });
}

/**
 * Manage the events
 */
void MainScene::loop_event()
{
    Event event;
    while (App::getInstance()->pollEvent(event))
    {
        // Action on Window Closed Event
        if (event.type == sf::Event::Closed)
            App::getInstance()->close();

        // Get mouse_pos in the window
        pos_mouse = Mouse::getPosition(*App::getInstance());
        mouse_coord = App::getInstance()->mapPixelToCoords(pos_mouse);

        // Zooming with the mousewheel
        if (!appear && !disp && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            int d = event.mouseWheelScroll.delta;
            if (d != -1 && d != 1)
                break;
            scl += event.mouseWheelScroll.delta;
        }

        // if (event.type == Event::EventType::KeyPressed){
        //     (Controller::getInstance()).makeKeyAction(event.key.code);
        // }
        // else
        //     (Controller::getInstance()).makeAction(event);
    }

    if(!Mouse::isButtonPressed(Mouse::Left))
    {
        left_pressed = false;
    }

    // Right click -> offset
    if (!appear && !disp && Mouse::isButtonPressed(Mouse::Right))
    {
        if (right_pressed)
        {
            Vector2f dv = mouse_coord - old_pos;
            off += dv;
        }
        else
            right_pressed = true;
        old_pos = mouse_coord;
    }
    else
    {
        right_pressed = false;
    }

    // Draw a blue rectangle on the Case where the mouse is
    if (board.getGlobalBounds().contains(mouse_coord))
    {
        Vector2f m = mouse_coord - board.getPosition() - off;
        if (m.x < 0)
            m.x -= scl;
        int x = m.x / scl;
        if (m.y < 0)
            m.y -= scl;
        int y = m.y / scl;

        int x0 = x;
        int y0 = y;

        x *= scl;
        y *= scl;

        setup_rect(rect, x, y);
        // Defining Color::Blue with a different alpha
        Color c{0, 0, 255, 100};

        rect.setFillColor(c);

        // if click -> add coord to the vector pos
        if (!left_pressed && Mouse::isButtonPressed(Mouse::Left))
        {   
            left_pressed = true;
            DomPiece &p = (DomPiece &)game->draw();
            cout << p << endl;
            pos.push_back(new DomPieceDisplayer{x0, y0, p});
        }
    }
    else
        rect.setFillColor(Color::Transparent);
}

/**
 * Change the rectangle to a new that is correctly calculated to render like the grid
 * @param r a rectangle which is going to change
 * @param x coord x of the mouse in the board
 * @param y coord y of the mouse in the board
 */
void MainScene::setup_rect(RectangleShape &r, float x, float y)
{
    int sclX = scl;
    int sclY = scl;
    if (x < -off.x)
    {
        sclX = x + off.x + scl;
        x = -off.x;
    }
    if (y < -off.y)
    {
        sclY = y + off.y + scl;
        y = -off.y;
    }
    if (x + scl > board.getGlobalBounds().width - off.x)
        sclX = -x + board.getGlobalBounds().width - off.x;
    if (y + scl > board.getGlobalBounds().height - off.y)
        sclY = -y + board.getGlobalBounds().height - off.y;

    r.setSize(Vector2f(sclX, sclY));

    r.setPosition(Vector2f(x, y) + board.getPosition() + off);
}

/**
 * Render the scene
 */
void MainScene::render()
{
    // appearing
    if (appear)
        display();
    // disappearing and change scene after
    if (disp)
    {
        dispose();
        if (!disp)
        {
            // CHANGEMENT DE SCENE
        }
    }
    // draw scoreboard, board, the current rect of the mouse
    App::getInstance()->draw(board);
    App::getInstance()->draw(rect);

    // Draw all the Pieces
    // TODO : Generalize it depending on gamemode
    for (PieceDisplayer *p : pos)
    {
        p->render(off, board, scl);
    }
    this->redrawBG();
    App::getInstance()->draw(scoreBoard);


}



/**
 * When the scene is appearing
 */
void MainScene::display()
{
    bool f1 = false;
    bool f2 = false;

    Vector2f pos_s = scoreBoard.getPosition();
    if (pos_s.x > (App::getInstance()->getWidth() * 4.0) / 5)
    {
        pos_s.x -= App::getInstance()->getWidth() / (5.0 * speed1);
        scoreBoard.setPosition(pos_s);
    }
    else
        f1 = true;

    pos_s = board.getPosition();
    if (pos_s.y > (App::getInstance()->getHeight() / 36))
    {
        pos_s.y -= App::getInstance()->getHeight() / (36.0 * speed2);
        board.setPosition(pos_s);
    }
    else
        f2 = true;
    if (f1 && f2)
        appear = false;
}

/**
 * When the scene is disappearing
 */
void MainScene::dispose()
{
}

void MainScene::redrawBG()
{
    Vector2f vB = board.getPosition();
    Vector2f bB {board.getGlobalBounds().width, board.getGlobalBounds().height};

    // rectBG.setFillColor(Color::Red);
    rectBG.setPosition(0, 0);
    //rectBG.setOutlineColor(Color::Red);
    //rectBG.setOutlineThickness(3);
   // rectBG.setScale(1, App::getInstance()->getHeight() / vB.y);
    rectBG.setTextureRect(IntRect{0, 0, App::getInstance()->getWidth() / rectBG.getScale().x , vB.y / rectBG.getScale().y});
    rectBG.setSize({App::getInstance()->getWidth() / rectBG.getScale().x, vB.y / rectBG.getScale().y});
    App::getInstance()->draw(rectBG);

    rectBG.setTextureRect(IntRect{0, 0, vB.x / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    rectBG.setSize({vB.x / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    App::getInstance()->draw(rectBG);

    rectBG.setPosition(vB.x + bB.x, 0);
    rectBG.setTextureRect(IntRect{(vB.x + bB.x) / rectBG.getScale().x, 0, App::getInstance()->getWidth() / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    rectBG.setSize({App::getInstance()->getWidth() / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    App::getInstance()->draw(rectBG);

    rectBG.setPosition(0, vB.y + bB.y);
    rectBG.setTextureRect(IntRect{0, (vB.y + bB.y) / rectBG.getScale().y, App::getInstance()->getWidth() / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    rectBG.setSize({App::getInstance()->getWidth() / rectBG.getScale().x , App::getInstance()->getHeight() / rectBG.getScale().y});
    App::getInstance()->draw(rectBG);


}