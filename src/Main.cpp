#include "front/App.hpp"

int main(int argc, char **argv)
{
    
    App app{};
    if(argc == 1) 
        app.runApp(0);
    else app.runApp(1);
    
    return EXIT_SUCCESS;
}
