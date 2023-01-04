#include "front/App.hpp"

int main(int argc, char **argv)
{
    
    if(argc == 1) 
    {
        App app{0};
        app.runApp(0);
    }
    else {
        int mode = atoi(argv[1]);
        App app{atoi(argv[1])};
        if(mode == 1) app.runApp(0);
        else app.runApp(1);
    }
    
    return EXIT_SUCCESS;
}
