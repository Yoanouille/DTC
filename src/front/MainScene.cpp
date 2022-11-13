#include "front/MainScene.hpp"

using namespace sf;
using namespace std;

MainScene::MainScene(Menu &m) : menu{m}, scoreBoard{}, board{}, scl{75}, off{180, 180}, rect{}, pos_mouse{0, 0}, mouse_coord{0, 0}, pos{}, right_pressed{false}, old_pos{0, 0}, disp{false}, app{true}
{
    init();
}

MainScene::~MainScene() {}

void MainScene::init()
{
    scoreBoard.setSize(Vector2f(menu.get_width() / 5, menu.get_height()));
    scoreBoard.setPosition(Vector2f((menu.get_width() * 6.0) / 5, 0));
    scoreBoard.setFillColor(Color::White);

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

void MainScene::loop_event()
{
    Event event;
    while (menu.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            menu.close();

        pos_mouse = Mouse::getPosition(menu);
        mouse_coord = menu.mapPixelToCoords(pos_mouse);

        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            // cout << event.mouseWheelScroll.delta << endl;
            int d = event.mouseWheelScroll.delta;
            if (d != -1 && d != 1)
                break;
            // if(scl <= 40 && d == -1) break;
            scl += event.mouseWheelScroll.delta;
        }
    }

    if (!app && !disp && Mouse::isButtonPressed(Mouse::Right))
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

    if (board.getGlobalBounds().contains(mouse_coord))
    {
        Vector2f m = mouse_coord - board.getPosition() - off;
        if (m.x < 0)
            m.x -= scl;
        int x = m.x / scl;
        x *= scl;
        if (m.y < 0)
            m.y -= scl;
        int y = m.y / scl;
        y *= scl;

        setup_rect(rect, x, y);

        Color c{0, 0, 255, 100};

        rect.setFillColor(c);

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2f v = rect.getPosition() - board.getPosition() - off;
            v.x = (int)v.x / scl;
            v.y = (int)v.y / scl;

            pos.push_back(v);
        }
    }
    else
    {
        rect.setFillColor(Color::Transparent);
    }
}

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

void MainScene::render()
{
    if (app)
        display();
    if (disp)
    {
        dispose();
        if (!disp)
        {
            // CHANGEMENT DE SCENE
        }
    }
    menu.draw(scoreBoard);
    menu.draw(board);
    menu.draw(rect);
    for (size_t i = 0; i < pos.size(); i++)
    {
        RectangleShape r{};

        Vector2f v = pos[i];
        setup_rect(r, v.x * scl, v.y * scl);

        if (board.getGlobalBounds().intersects(r.getGlobalBounds()))
        {
            r.setFillColor(Color::Green);
            menu.draw(r);
        }
    }
}

void MainScene::display()
{
    bool f1 = false;
    bool f2 = false;

    Vector2f pos_s = scoreBoard.getPosition();
    if (pos_s.x > (menu.get_width() * 4.0) / 5)
    {
        pos_s.x -= menu.get_width() / (5.0 * 420);
        scoreBoard.setPosition(pos_s);
    }
    else
        f1 = true;

    pos_s = board.getPosition();
    if (pos_s.y > (menu.get_height() / 36))
    {
        pos_s.y -= menu.get_height() / (36.0 * 30);
        board.setPosition(pos_s);
    }
    else
        f2 = true;
    if (f1 && f2)
        app = false;
}

void MainScene::dispose() {}