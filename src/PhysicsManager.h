#pragma once

#include "RigidBody.h"
#include "Utilities.h"

extern int FRAMES;

class World {
    float dt = 1.0/FRAMES;    
    std::vector<std::unique_ptr<RigidBody>> rigidBodies;
    std::vector<Vector2> globalForces;

    public:
    float getDt() const;
    void update(); //constantly called
    void start(); //called at begining of simulation

    
};