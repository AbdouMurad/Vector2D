#include "PhysicsManager.h"

#ifdef ULTRA
int FRAMES = 120;
#else
int FRAMES = 60;
#endif

void World::start() {
    rigidBodies.push_back(std::make_unique<RigidBody>(Vector2(0,100),Vector2(0,0),Vector2(0,0)));
    globalAcceleration.push_back(Vector2(0,-9.81)); //gravity

}

void World::update() {
    for (int i = 0; i < rigidBodies.size(); ++i) {
        for (int j = 0; j < globalAcceleration.size(); ++j) rigidBodies[i]->applyForce(globalAcceleration[j] * rigidBodies[i]->getMass());
        rigidBodies[i]->integrate(dt);
        std::cout << *rigidBodies[i] << std::endl;
    }
}

float World::getDt () const {
    return dt;
}