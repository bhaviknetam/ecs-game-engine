#pragma once

#include "SDL2/SDL.h"
#include <string>

#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "../AssetManager/AssetManager.h"

class Sprite : public Component
{
private:
    int width = 0;
    int heigth = 0;
    SDL_Rect srcRect = {0, 0, 0, 0};
    SDL_Rect destRect = {0, 0, 0, 0};

    Transform *transform = nullptr;
    SDL_Texture *texture = nullptr;
    std::string textureID = "";
    SDL_Renderer *targetRenderer = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
    Sprite(/* args */) = default;
    virtual ~Sprite() = default;

    Sprite(SDL_Renderer *target, std::string textureid) : targetRenderer(target), textureID(textureid) {}

    bool init() override final
    {
        transform = &entity->getComponent<Transform>();
        if (!transform)
        {
            SDL_Log("Error: Transform component not found");
            return false;
        }
        texture = AssetManager::getInstance()->getTexture(textureID);
        if (!texture)
        {
            SDL_Log("Error: Texture [%s] not found", textureID.c_str());
            return false;
        }
        if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &heigth) != 0)
        {
            SDL_Log("Error in Texture Query: %s", SDL_GetError());
            return false;
        }
        srcRect = {0, 0, width, heigth};
        return true;
    }

    void draw() override final
    {
        SDL_RenderCopyEx(targetRenderer, texture, &srcRect, &destRect, transform->rotation, NULL, flip);
    }

    void update() override final
    {
        destRect.x = static_cast<int>(transform->pos.x);
        destRect.y = static_cast<int>(transform->pos.y);
        destRect.w = static_cast<int>(width * transform->scale.x);
        destRect.h = static_cast<int>(heigth * transform->scale.y);
    }
};