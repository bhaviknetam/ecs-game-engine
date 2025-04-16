#define SDL_MAIN_HANDLED
#include "Engine/Engine.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    if (!Engine::getInstance()->Init())
    {
        std::cerr << "Engine initialization failed!" << std::endl;
    }
    while (Engine::getInstance()->isRunning())
    {
        // std::cout << "Running..." << std::endl;
        Engine::getInstance()->Event();
        Engine::getInstance()->Update();
        Engine::getInstance()->Render();
    }
    Engine::getInstance()->Clean();
    return 0;
}
