#include "RigidBody.h"
#include "Utilities.h"

#ifdef ULTRA
float FRAMES = 120;
#else
float FRAMES = 60;
#endif

class World {
    float dt = 1.0/FRAMES;    
    std::vector<std::unique_ptr<RigidBody>> rigidBodies;
    std::vector<Vector2> globalForces;

    public:

    void update(); //constantly called
    void start(); //called at begining of simulation

    
};