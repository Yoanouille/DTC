#include "front/MainScene.hpp"
#include "front/TraxPieceDisplayer.hpp"
#include "front/CarcPieceDisplayer.hpp"
#include "front/DomPieceDisplayer.hpp"
#include "back/Domino.hpp"
#include "front/AssetsLoader.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 * Initialize some variables, call init()
 */
MainScene::MainScene(App &app, int gamemode, vector<string> &names) : 
    app{app}, scoreBoard{app}, drawZone{app, gamemode == TRAX},
    board{}, scl{150}, off{180, 180}, 
    rect{}, rectBG{}, pos_mouse{0, 0}, mouse_coord{0, 0}, 
    pos{}, right_pressed{false}, left_pressed{false}, old_pos{0, 0}, 
    disp{false}, appear{true}, speed1{40}, speed2{3},
    current_piece{nullptr}
{
    for (string s : names)
        app.getGame()->addPlayer(s);
    scoreBoard.setGame(app.getGame());
    init();
}

/**
 * Destructor
 */
MainScene::~MainScene() 
{
    if(current_piece != nullptr) delete current_piece;
    for(PieceDisplayer *p : pos)
        delete p;
}

/**
 * initialize the scene
 */
void MainScene::init()
{
    // Setup the board
    double dx = (app.getWidth() - scoreBoard.getSize().x);
    board.setSize(Vector2f((dx * 13.0f) / 15.0f, app.getHeight() * 17 / 18));
    board.setPosition(Vector2f(app.getWidth() / 32.0, app.getHeight() * 38.0 / 36));
    // RGBA format
    Color c{0, 0, 0, 200};
    board.setFillColor(c);

    rectBG.setTexture(&Assets::getInstance()->MainMenuBackground);
    rectBG.setScale(0.33, 0.33);

    initBoard();


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

void MainScene::initBoard()
{
    int gamemode = app.getGamemode();
    vector<PiecePos> v = app.getGame()->getAllPiece();
    for(PiecePos &pi : v)
    {
        if(gamemode == DOMINO)
            pos.push_back(new DomPieceDisplayer(app, pi.j, pi.i, (DomPiece &)(*pi.p)));
        if(gamemode == TRAX)
            pos.push_back(new TraxPieceDisplayer(app, pi.j, pi.i, (TraxPiece &)(*pi.p)));
        if(gamemode == CARCASSONNE)
            pos.push_back(new CarcPieceDisplayer(app, pi.j, pi.i, (CarcPiece &)(*pi.p)));
    }
}

/**
 * Manage the events
 */
void MainScene::loop_event()
{
    Event event{};
    while (app.pollEvent(event))
    {
        // Action on Window Closed Event
        if (event.type == sf::Event::Closed)
            app.close();

        // Get mouse_pos in the window
        pos_mouse = Mouse::getPosition(app);
        mouse_coord = app.mapPixelToCoords(pos_mouse);


        if (!appear && !disp) {
            drawZone.sack.handleClick(mouse_coord);
            drawZone.rotateLeft.handleClick(mouse_coord);
            drawZone.rotateRight.handleClick(mouse_coord);
            if(app.getGamemode() == TRAX) drawZone.flipButton.handleClick(mouse_coord);
            else drawZone.passButton.handleClick(mouse_coord);

            // Zooming with the mousewheel
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                int d = event.mouseWheelScroll.delta;
                if (d != -1 && d != 1)
                    break;
                scl += event.mouseWheelScroll.delta;
            }
        }
    }

    if(!Mouse::isButtonPressed(Mouse::Left))
    {
        left_pressed = false;
        drawZone.sack.setClicked(false);
        drawZone.rotateLeft.setClicked(false);
        drawZone.rotateRight.setClicked(false);
        drawZone.passButton.setClicked(false);
        if (app.getGamemode() == TRAX) drawZone.flipButton.setClicked(false);
    }

    // Right click -> offset
    if (!appear && !disp && Mouse::isButtonPressed(Mouse::Right))
    {
        moveBoard();
    }
    else
    {
        right_pressed = false;
    }

    // Draw a blue rectangle on the Case where the mouse is
    if (board.getGlobalBounds().contains(mouse_coord))
    {
        drawRectAndPlay();
    }
    else
        rect.setFillColor(Color::Transparent);
}

void MainScene::moveBoard()
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

void MainScene::drawRectAndPlay()
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

    if(current_piece != nullptr)
    {
        if(!left_pressed && Mouse::isButtonPressed(Mouse::Left))
        {
            left_pressed == true;
            current_piece->handleClick(mouse_coord, app.getGame()->getPlayers()[app.getGame()->getCurrentPlayer()], app.getGame()->getCurrentPlayer(), scl);

            x0 = current_piece->getCoord().x;
            y0 = current_piece->getCoord().y;
            if(!app.getGame()->canPlace(y0, x0, current_piece->getPiece())) 
            {
                //cout << "remove handle" << endl;
                current_piece->removeHandle(app.getGame()->getPlayers()[app.getGame()->getCurrentPlayer()], app.getGame()->getCurrentPlayer());
                return;
            }
            current_piece->nextState();

            place();
            
        }
    }
    else if(drawZone.getPieceViewer() != nullptr)
    {
        if(app.getGame()->canPlace(y0, x0, drawZone.getPieceViewer()->getPiece()))
        {
            if (!left_pressed && Mouse::isButtonPressed(Mouse::Left))
            {
                current_piece = drawZone.pick();
                current_piece->setPos(x0,y0);
                current_piece->nextState();
                pos.push_back(current_piece);
                left_pressed = true;

                place();
            } else rect.setFillColor({0, 255, 0, 100});
        } else rect.setFillColor({255, 0, 0, 100});
    }
}

void MainScene::place()
{
    if(current_piece->isFinalState())
    {
        cout << "app.getGame()->place(" << current_piece->getCoord().y << ", " << current_piece->getCoord().x << ", " << "*piece)" << ";" << endl;
        app.getGame()->place(current_piece->getCoord().y, current_piece->getCoord().x, current_piece->getPiece());
        scoreBoard.update();
        if(app.getGame()->gameOver()) 
        {
            app.setScene(4, 0, nullptr);
            //app.close();
        }
        current_piece = nullptr;
    }
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
    app.draw(board);
    app.draw(rect);

    // Draw all the Pieces
    for (PieceDisplayer *p : pos)
    {
        p->render(off, board, scl, mouse_coord);
    }
    this->redrawBG();
    scoreBoard.update();
    scoreBoard.render();
    drawZone.render();
}

/**
 * When the scene is appearing
 */
void MainScene::display()
{
    bool f1 = false;
    bool f2 = false;

    Vector2f pos_s = scoreBoard.getPosition();
    if (pos_s.x > (app.getWidth() * 4.0) / 5)
    {
        pos_s.x -= app.getWidth() / (5.0 * speed1);
        scoreBoard.setPosition(pos_s);
    }
    else
        f1 = true;

    pos_s = board.getPosition();
    if (pos_s.y > (app.getHeight() / 36))
    {
        pos_s.y -= app.getHeight() / (36.0 * speed2);
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
   // rectBG.setScale(1, app.getHeight() / vB.y);
    rectBG.setTextureRect({0, 0, app.getWidth() / rectBG.getScale().x , vB.y / rectBG.getScale().y});
    rectBG.setSize({app.getWidth() / rectBG.getScale().x, vB.y / rectBG.getScale().y});
    app.draw(rectBG);

    rectBG.setTextureRect({0, 0, vB.x / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    rectBG.setSize({vB.x / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    app.draw(rectBG);

    rectBG.setPosition(vB.x + bB.x, 0);
    rectBG.setTextureRect({(vB.x + bB.x) / rectBG.getScale().x, 0, app.getWidth() / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    rectBG.setSize({app.getWidth() / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    app.draw(rectBG);

    rectBG.setPosition(0, vB.y + bB.y);
    rectBG.setTextureRect({0, (vB.y + bB.y) / rectBG.getScale().y, app.getWidth() / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    rectBG.setSize({app.getWidth() / rectBG.getScale().x , app.getHeight() / rectBG.getScale().y});
    app.draw(rectBG);


}