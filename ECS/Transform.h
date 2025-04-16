#pragma once

#include "Component.h"
#include "Vect2D.h"

class Transform : public Component
{
public:
    Transform(/* args */) = default;
    Transform(float x, float y)
    {
        pos.x = x;
        pos.y = y;
    }

    Transform(float x, float y, float scx, float scy)
    {
        pos.x = x;
        pos.y = y;
        scale.x = scx;
        scale.y = scy;
    }

    Transform(float x, float y, float scx, float scy, float rot)
    {
        pos.x = x;
        pos.y = y;
        scale.x = scx;
        scale.y = scy;
        rotation = rot;
    }

    bool init() override final
    {
        return true;
    }

    void draw() override final
    {
    }

    virtual ~Transform() = default;

    Vect2F pos = Vect2F();
    Vect2F scale = Vect2F(1.0f, 1.0f);
    float rotation = 0.0f;
};