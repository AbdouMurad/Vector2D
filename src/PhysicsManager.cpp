#include "PhysicsManager.h"

#ifdef ULTRA
int FRAMES = 120;
#else
int FRAMES = 60;
#endif



void World::start() {
    rigidBodies.push_back(std::make_unique<RigidBody>(std::make_unique<Circle>(),Vector2(0,100),Vector2(0,0),Vector2(0,0))); 
    rigidBodies.push_back(std::make_unique<RigidBody>(Vector2(0,100),Vector2(0,0),Vector2(0,0))); 
    globalAcceleration.push_back(Vector2(0,-9.81)); //gravity
    //searchLargestDimension();
    //std::cout << largestDimension << std::endl;
    checkSAT(*rigidBodies[0], *rigidBodies[1]);
}

void World::update() {
    for (int i = 0; i < rigidBodies.size(); ++i) {
        for (int j = 0; j < globalAcceleration.size(); ++j) rigidBodies[i]->applyForce(globalAcceleration[j] * rigidBodies[i]->getMass());
        rigidBodies[i]->integrate(dt);
        //std::cout << *rigidBodies[i] << std::endl;
    }
}
void World::searchLargestDimension() {
    for (int i = 0; i < rigidBodies.size(); ++i) {
        largestDimension = max(largestDimension, rigidBodies[i]->getSize());
    }
} 
float World::getDt () const {
    return dt;
}

bool checkSAT(const RigidBody &rb1, const RigidBody &rb2) {
    if (!rb1.hasCollider() || !rb2.hasCollider()) return false;
    if (auto c1 = dynamic_cast<const Circle *>(rb1.getCollider())) {
        std::cout << "CIRCLE COLLIDER FOUND" << std::endl;
    }
    return true;
}