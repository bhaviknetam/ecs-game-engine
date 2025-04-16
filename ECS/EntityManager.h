#pragma once

#include "Entity.h"
#include <vector>
#include <memory>

class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    EntityManager(/* args */) {}
    ~EntityManager() {}
    void draw();
    void update();
    void refresh();
    void addEntity(Entity *player);
    void eraseEntity(Entity *player);
    Entity *cloneEntity(Entity *player);
};