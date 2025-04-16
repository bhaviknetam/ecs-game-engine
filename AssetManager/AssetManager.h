/* --- AssetManager.h --- */
#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void clean();

    SDL_Texture *getTexture(std::string id);
    void loadTexture(std::string id, std::string imgpath);

    TTF_Font *getFont(std::string id);
    void loadFont(std::string id, std::string fontpath, int fontsize);

    inline static AssetManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new AssetManager();
        }
        return instance;
    }

private:
    static AssetManager *instance;
    std::map<std::string, SDL_Texture *> textureMap;
    std::map<std::string, TTF_Font *> fontMap;
};
