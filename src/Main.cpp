#include "front/App.hpp"

int main()
{
    App app{};
    app.runApp();

    delete Assets::getInstance();
    
    return EXIT_SUCCESS;
}
