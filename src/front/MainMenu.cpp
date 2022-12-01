#include "front/MainMenu.hpp"

using namespace sf;
using namespace std;

/**
 * Constructor
 */
MainMenu::MainMenu(App &app) : Scene{}, app{app}, options{}, texts{}, pos_mouse{}, mouse_coord{}, disp{false}, appear{true}, speed{20}
{ 
    init(); 
}

/** Destructor */
MainMenu::~MainMenu() {}

/** Initialize the Scene */
void MainMenu::init()
{
    // Setup texts
    options = {"Domino", "Trax", "Carcassonne"};
    texts.resize(options.size());
    for (std::size_t i{}; i < texts.size(); ++i)
    {
        texts[i].setFont(Assets::getInstance()->MainMenuFont);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(75);
        Color c{255, 255, 255, 0};
        texts[i].setFillColor(c);
        FloatRect r = texts[i].getGlobalBounds();
        texts[i].setOrigin(0.5 * r.width, 0.5 * r.height);
        texts[i].setPosition(app.getWidth() / 2, (i + 1) * app.getHeight() / (options.size() + 1));
    }
}

// Manage event
void MainMenu::loop_event()
{

    Event event;
    while (app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.close();

        pos_mouse = Mouse::getPosition(app);
        mouse_coord = app.mapPixelToCoords(pos_mouse);

        if (!appear && !disp && Mouse::isButtonPressed(Mouse::Left))
            for (size_t i = 0; i < texts.size(); i++)
            {
                if (texts[i].getGlobalBounds().contains(mouse_coord))
                {
                    // Change Scene to a Scene that sets players.
                    // maybe strore some variable to know which game it is
                    cout << "Changement de Scene" << endl;
                    disp = true;
                }
            }
    }

    /** If the mouse is on a text change his color to red
     * if not change his color to white
     */
    for (size_t i = 0; i < texts.size(); i++)
    {
        if (texts[i].getGlobalBounds().contains(mouse_coord))
        {
            Color c = texts[i].getFillColor();
            if (c.g >= speed)
                c.g -= speed; // speed
            if (c.b >= speed)
                c.b -= speed; // speed

            texts[i].setFillColor(c);
        }
        else
        {
            Color c = texts[i].getFillColor();
            if (c.g < 255 - speed)
                c.g += speed; // speed
            if (c.b < 255 - speed)
                c.b += speed; // speed

            texts[i].setFillColor(c);
        }
    }
}

void MainMenu::render()
{
    if (appear) 
        display();
    if (disp)
    {
        dispose();
        if (!disp)
        {
            // DIRE DE CHANGER DE SCENE
            app.setScene(2);
        }
    }
    // draw text
    for (Text &t : texts)
    {
        app.draw(t);
    }
}

/**
 * Disappearing of the scene
 */
void MainMenu::dispose()
{
    if (!disp)
        return;
    for (Text &t : texts)
    {
        Color c = t.getFillColor();
        c.a -= speed;
        t.setFillColor(c);
        if (c.a < speed)
        {
            disp = false;
        }
    }
}

/**
 * Appearing of the Scene
 */
void MainMenu::display()
{
    for (Text &t : texts)
    {
        Color c = t.getFillColor();
        c.a += speed;
        t.setFillColor(c);
        if (c.a > 255 - speed)
            appear = false;
    }
}