/* --- AssetManager.cpp --- */

#include "AssetManager.h"
#include "../Engine/Engine.h"
#include <iostream>

AssetManager *AssetManager::instance = nullptr;

AssetManager::AssetManager()
{
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_Log("Error in IMG_Init: %s", IMG_GetError());
    }
    if (TTF_Init() != 0)
    {
        SDL_Log("Error in TTF_Init: %s", TTF_GetError());
    }
}

SDL_Texture *AssetManager::getTexture(std::string id)
{
    return (textureMap.count(id) ? textureMap[id] : nullptr);
}

void AssetManager::loadTexture(std::string id, std::string imgpath)
{
    if (!textureMap.count(id))
    {
        SDL_Texture *texture = IMG_LoadTexture(Engine::getInstance()->getRenderer(), imgpath.c_str());
        if (texture)
        {
            textureMap[id] = texture;
            std::cout << "Texture Loaded" << std::endl;
        }
        else
        {
            SDL_Log("Error in load texture: %s", IMG_GetError());
        }
    }
}

void AssetManager::loadFont(std::string id, std::string fontpath, int fontsize)
{
    TTF_Font *font = TTF_OpenFont(fontpath.c_str(), fontsize);
    if (font)
    {
        fontMap[id] = font;
        std::cout << "font: [" << fontpath << "] loaded" << std::endl;
    }
    else
    {
        SDL_Log("Error in Load Font: %s", TTF_GetError());
    }
}

TTF_Font *AssetManager::getFont(std::string id)
{
    return (fontMap.count(id) ? fontMap[id] : nullptr);
}

void AssetManager::clean()
{
    for (auto &it : textureMap)
    {
        SDL_DestroyTexture(it.second);
    }
    textureMap.clear();
    for (auto &it : fontMap)
    {
        TTF_CloseFont(it.second);
    }
    fontMap.clear();
    IMG_Quit();
    TTF_Quit();
}