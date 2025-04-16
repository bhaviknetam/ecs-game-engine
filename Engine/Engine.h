/* --- Engine.h --- */

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "../ECS/EntityManager.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine
{
private:
    bool running;
    static Engine *instance;
    EntityManager *manager;
    SDL_Color clearColor;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Engine() : running(false), window(nullptr), renderer(nullptr) {}

public:
    static Engine *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Engine();
        }
        return instance;
    }

    inline SDL_Renderer *getRenderer() { return renderer; }
    inline bool isRunning() { return running; }
    bool Init();
    bool Clean();
    void Event();
    void Quit();
    void Update();
    void Render();
};

#endif // ENGINE_H
