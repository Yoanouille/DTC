#include "front/MainScene.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 * Initialize some variables, call init()
*/
MainScene::MainScene(Menu &m) : menu{m}, scoreBoard{}, board{}, scl{75}, off{180, 180}, rect{}, pos_mouse{0, 0}, mouse_coord{0, 0}, pos{}, right_pressed{false}, old_pos{0, 0}, disp{false}, app{true}
{
    init();
}

/**
 * Destructor
*/
MainScene::~MainScene()
{

}

/**
 * initialize the scene
*/
void MainScene::init()
{
    //setup the scoreboard
    scoreBoard.setSize(Vector2f(menu.get_width() / 5, menu.get_height()));
    scoreBoard.setPosition(Vector2f((menu.get_width() * 6.0) / 5, 0));
    scoreBoard.setFillColor(Color::White);

    //setup the board
    double dx = (menu.get_width() - scoreBoard.getSize().x);
    board.setSize(Vector2f(dx * 15.0 / 16, menu.get_height() * 17 / 18));
    board.setPosition(Vector2f(menu.get_width() / 32.0, menu.get_height() * 38.0 / 36));
    Color c{};
    c.r = 0;
    c.g = 0;
    c.b = 0;
    c.a = 200;
    board.setFillColor(c);
}

/**
 * Manage the event
*/
void MainScene::loop_event()
{
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            menu.close();

        pos_mouse = Mouse::getPosition(menu);
        mouse_coord = menu.mapPixelToCoords(pos_mouse);

        //Zooming with the mousewheel
        if(!app && !disp && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            int d = event.mouseWheelScroll.delta;
            if(d != -1 && d != 1) break;
            scl += event.mouseWheelScroll.delta;
        }

    }

    //Right click -> offset
    if(!app && !disp && Mouse::isButtonPressed(Mouse::Right))
    {
        if(right_pressed)
        {
            Vector2f dv = mouse_coord - old_pos;
            off += dv;
        } else right_pressed = true;
        old_pos = mouse_coord;
    } else {
        right_pressed = false;
    }

    //Just position of the mouse -> draw the blue rect
    if(board.getGlobalBounds().contains(mouse_coord))
    {
        Vector2f m = mouse_coord - board.getPosition() - off; 
        if(m.x < 0) m.x -= scl;
        int x = m.x / scl;
        if(m.y < 0) m.y -= scl;
        int y = m.y / scl;

        int x0 = x;
        int y0 = y;

        x *= scl;
        y *= scl;
        
      
        setup_rect(rect, x, y);

        Color c{0, 0, 255, 100};

        rect.setFillColor(c);

        //if click -> add coord to the vector pos
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            // Vector2f v = rect.getPosition() - board.getPosition() - off;
            // if(rect.getPosition().x <= board.getPosition().x + 0.1) v.x = (int) v.x / scl - 1;
            // else v.x = (int) v.x / scl;
            // if(rect.getPosition().y <= board.getPosition().y + 0.1) v.y = (int) v.y / scl - 1;
            // else v.y = (int) v.y / scl;
            Vector2f v = {x0, y0};
            pos.push_back(v);

        }


    } else 
    {
        rect.setFillColor(Color::Transparent);
    }
}

/**
 * Change the rectangle to a new that is correctly calculated to render like the grid
 * @param r a rectangle which is going to change
 * @param x coord x of the mouse in the board
 * @param y coord y of the mouse in the board
*/
void MainScene::setup_rect(RectangleShape &r, float  x, float y)
{  
    int sclX = scl;
    int sclY = scl;
    if(x < -off.x) 
    {
        sclX = x + off.x + scl;
        x = -off.x;
    }
    if(y < -off.y)
    {
        sclY = y + off.y + scl;
        y = -off.y;
    }
    if(x + scl > board.getGlobalBounds().width - off.x) sclX = - x + board.getGlobalBounds().width - off.x;
    if(y + scl > board.getGlobalBounds().height - off.y) sclY = - y + board.getGlobalBounds().height - off.y;

    r.setSize(Vector2f(sclX, sclY));


    r.setPosition(Vector2f(x, y) + board.getPosition() + off);


}


/**
 * Render the scene
*/
void MainScene::render()
{
    //appearing
    if(app) display();
    //disappearing and change scene after
    if(disp)
    {
        dispose();
        if(!disp) {
            //CHANGEMENT DE SCENE
        }
    }
    //draw scoreboard, board, the current rect of the mouse
    menu.draw(scoreBoard);
    menu.draw(board);
    menu.draw(rect);

    //draw green rect in the vector pos
    for(size_t i = 0; i < pos.size(); i++)
    {
        RectangleShape r{};

        Vector2f v = pos[i];
        setup_rect(r, v.x * scl, v.y * scl);
        if(r.getSize().x < 0 || r.getSize().y < 0) continue; 

        if(r.getGlobalBounds().intersects(board.getGlobalBounds()))
        {
            r.setFillColor(Color::Green); 
            menu.draw(r);
        }

    }
}

/**
 * When the scene is appearing
*/
void MainScene::display()
{
    bool f1 = false;
    bool f2 = false;

    Vector2f pos_s = scoreBoard.getPosition();
    if(pos_s.x > (menu.get_width() * 4.0) / 5)
    {
        pos_s.x -= menu.get_width() / (5.0 * 420); //420 manage the speed
        scoreBoard.setPosition(pos_s);
    } else f1 = true;

    pos_s = board.getPosition();
    if(pos_s.y > (menu.get_height() / 36))
    {
        pos_s.y -= menu.get_height() / (36.0 * 30); // 30 manage the speed
        board.setPosition(pos_s);
    } else f2 = true;
    if(f1 && f2) app = false;
}

/**
 * When the scene is disappearing
*/
void MainScene::dispose()
{

}