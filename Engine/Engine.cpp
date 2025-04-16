/* --- Engine.cpp --- */

#include "Engine.h"
#include "../AssetManager/AssetManager.h"
#include "../ECS/EntityManager.h"
#include "../ECS/Sprite.h"

Engine *Engine::instance = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Error in Init(): %s", SDL_GetError());
        return false;
    }
    auto wflags = (SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, wflags);
    if (!window)
    {
        SDL_Log("Error in creating window: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("Error in creating renderer: %s", SDL_GetError());
        return false;
    }
    AssetManager::getInstance()->loadTexture("test", "assets/test.png");
    manager = new EntityManager();
    Entity *e = new Entity();
    e->getComponent<Transform>().pos = {100, 100};
    printf("Adding Sprite component\n");
    e->addComponent<Sprite>(renderer, "test");
    printf("Add entity\n");
    manager->addEntity(e);
    return running = true;
}

bool Engine::Clean()
{
    AssetManager::getInstance()->clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return true;
}

void Engine::Quit()
{
    running = false;
}

void Engine::Event()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            Quit();
        }
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                Quit();
                break;
            default:
                break;
            }
        }
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    manager->draw();
    SDL_RenderPresent(renderer);
}

void Engine::Update()
{
    manager->update();
}
