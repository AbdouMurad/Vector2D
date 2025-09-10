#pragma once
#include "Utilities.h"
#include <iostream>

class Entity {
    friend std::ostream &operator<<(std::ostream &out, const Entity &other);
    
    protected:
    Vector2 *position;

    public:
    float rotation;
    
    void setPosition(const Vector2 &v);
    Vector2 getPosition() const;
    
    ~Entity();
    Entity();
    Entity(const Vector2 &v);
    Entity(const Entity &e);

    
};

std::ostream &operator<<(std::ostream &out, const Entity &other);