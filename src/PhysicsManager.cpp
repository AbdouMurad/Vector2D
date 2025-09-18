#include "PhysicsManager.h"

#ifdef ULTRA
int FRAMES = 120;
#else
int FRAMES = 60;
#endif

void World::start() {
    rigidBodies.push_back(std::make_unique<RigidBody>(Vector2(0,0),Vector2(10,0),Vector2(0,0)));
    rigidBodies.push_back(std::make_unique<RigidBody>(Vector2(0,0),Vector2(-10,0),Vector2(0,0)));
    
}

void World::update() {
    Timer timer;
    for (int i = 0; i < rigidBodies.size(); ++i) {
        rigidBodies[i]->integrate(dt);
        std::cout << *rigidBodies[i] << std::endl;
    }
}

float World::getDt () const {
    return dt;
}