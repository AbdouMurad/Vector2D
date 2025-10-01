#include "Utilities.h"
#include "PhysicsManager.h"
#include "RigidBody.h"
#include <iostream>


int main() {
    World world;
    //game loop

    auto start = std::chrono::high_resolution_clock::now();
    world.start();
    
    while (true) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        if (duration.count() >= world.getDt()) {
            world.update();
            start = end;
        }
    }
}