#pragma once

class Entity;

class Component
{
public:
    Component(/* args */) {}
    ~Component() {}

    Entity *entity;

    virtual bool init() { return true; }
    virtual void draw() {}
    virtual void update() {}
};