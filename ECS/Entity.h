#pragma once

#include "ECS.h"
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <memory>

class Entity
{
private:
    bool active;
    ComponentList compList;
    ComponentBitset compBitset;
    std::vector<std::unique_ptr<Component>> components;

public:
    Entity()
    {
        this->addComponent<Transform>();
        std::cout << "Transform component added to entity" << std::endl;
    }

    template <typename T, typename... TArgs>
    inline T &addComponent(TArgs &&...args)
    {
        T *comp = new T(std::forward<TArgs>(args)...);

        comp->entity = this;
        std::unique_ptr<Component> uptr(comp);

        if (comp->init())
        {
            std::cout << "Component initialized" << std::endl;
            compList[getComponentTypeID<T>()] = comp;
            compBitset[getComponentTypeID<T>()] = comp;
            components.emplace_back(std::move(uptr));
            return *comp;
        }
        std::cout << "Component not initialized" << std::endl;
        delete comp;
        return *static_cast<T *>(nullptr);
    }

    template <typename T>
    inline T &getComponent() const
    {
        auto ptr = compList[getComponentTypeID<T>()];
        std::cout << "Get component" << std::endl;
        return *static_cast<T *>(ptr);
    }

    template <typename T>
    inline bool hasComponent()
    {
        return compBitset[getComponentTypeID<T>()];
    }

    inline bool isActive() { return active; }
    inline void destroy() { active = false; }
    inline void draw()
    {
        for (auto &comp : components)
        {
            comp->draw();
        }
    }
    inline void update()
    {
        for (auto &comp : components)
        {
            comp->update();
        }
    }
};
