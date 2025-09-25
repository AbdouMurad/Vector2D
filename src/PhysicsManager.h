#pragma once

#include "RigidBody.h"
#include "Utilities.h"

extern int FRAMES;

class World {
    float largestDimension = 0;
    float dt = 1/FRAMES;  
    std::vector<std::unique_ptr<RigidBody>> rigidBodies;
    std::vector<Vector2> globalAcceleration; //forces like gravity
    void searchLargestDimension();
    public:
    float getDt() const;
    void update(); //constantly called
    void start(); //called at begining of simulation

    
};