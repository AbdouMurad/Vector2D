#include "PhysicsManager.h"

#ifdef ULTRA
int FRAMES = 120;
#else
int FRAMES = 60;
#endif



void World::start() {
    rigidBodies.push_back(std::make_unique<RigidBody>(std::make_unique<Rectangle>(),Vector2(10,0),Vector2(-3,0),Vector2(0,0))); 
    rigidBodies.push_back(std::make_unique<RigidBody>(std::make_unique<Rectangle>(),Vector2(-10,0),Vector2(3,0),Vector2(0,0))); 


    //globalAcceleration.push_back(Vector2(0,-9.81)); //gravity
    //searchLargestDimension();
    //std::cout << largestDimension << std::endl;
    {
        Timer timer;
        std::cout << "COLLIDING: " << checkSAT(*rigidBodies[0], *rigidBodies[1]) << std::endl;
    }
}

void World::update() {
    for (int i = 0; i < rigidBodies.size(); ++i) {
        for (int j = 0; j < globalAcceleration.size(); ++j) rigidBodies[i]->applyForce(globalAcceleration[j] * rigidBodies[i]->getMass());
        rigidBodies[i]->integrate(dt);
        std::cout << *rigidBodies[i] << std::endl;
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
        if (auto c2 = dynamic_cast<const Circle *>(rb2.getCollider())) {
            return CCSAT(rb1, c1, rb2, c2);
        }
        else if (auto c2 = dynamic_cast<const Rectangle *>(rb2.getCollider())) {
            //circle x rectangle
        }
    }
    else if (auto c1 = dynamic_cast<const Rectangle *>(rb1.getCollider())) {
        if (auto c2 = dynamic_cast<const Rectangle *>(rb2.getCollider())) {
            return RRSAT(rb1, c1, rb2, c2);
        }
        else if (auto c2 = dynamic_cast<const Circle *>(rb2.getCollider())) {
            //rectangle x circle
        }
    }
    return false;
}

bool CCSAT(const RigidBody &rb1, const Circle *c1, const RigidBody &rb2, const Circle *c2) {
    float d = distance(rb1.getPosition(), rb2.getPosition());
    return (c1->getRadius() + c2->getRadius()) < d ? false : true;

}
//RRSAT HELPER
bool checkAxes(const Vector2 *corners1, const Vector2 *corners2, const Vector2 &axes) {
    float r1_min = projectLength(axes, corners1[0]);
    float r1_max = r1_min;
    float r2_min = projectLength(axes, corners2[0]);
    float r2_max = r2_min;

    float proj = 0;
    for (int i = 0; i < 4; ++i) {
        proj = projectLength(axes, corners1[i]);
        r1_min = min(r1_min, proj);
        r1_max = max(r1_max, proj);

        proj = projectLength(axes, corners2[i]);
        r2_min = min(r2_min, proj);
        r2_max = max(r2_max, proj);
    }

    return !(r1_max < r2_min || r1_min > r2_max);

}
bool RRSAT(const RigidBody &rb1, const Rectangle *r1, const RigidBody &rb2, const Rectangle *r2) {
    //find 4 corners of rb1
    double rb1_rotation = rb1.getRotation();
    float distanceCorner = Vector2(r1->getWidth()/2, r1->getHeight()/2).length();
    Vector2 corners1[4];
    //bottom left
    corners1[0] = Vector2(rb1.getPosition() + Vector2(distanceCorner * cos(rb1_rotation - 3 * PI/4), distanceCorner * sin(rb1_rotation - 3 * PI/4)));
    //top left
    corners1[1] = Vector2(rb1.getPosition() + Vector2(distanceCorner * cos(rb1_rotation + 3 * PI/4), distanceCorner * sin(rb1_rotation +3 * PI/4)));
    //top right
    corners1[2] = Vector2(rb1.getPosition() + Vector2(distanceCorner * cos(rb1_rotation + PI/4), distanceCorner * sin(rb1_rotation + PI/4)));
    //bottom right
    corners1[3] = Vector2(rb1.getPosition() + Vector2(distanceCorner * cos(rb1_rotation - PI/4), distanceCorner * sin(rb1_rotation - PI/4)));
    
    //find 4 corners of rb2
    double rb2_rotation = rb2.getRotation();
    distanceCorner = Vector2(r2->getWidth()/2, r2->getHeight()/2).length();
    Vector2 corners2[4];
    //bottom left
    corners2[0] = Vector2(rb2.getPosition() + Vector2(distanceCorner * cos(rb2_rotation - 3 * PI/4), distanceCorner * sin(rb2_rotation - 3 * PI/4)));
    //top left
    corners2[1] = Vector2(rb2.getPosition() + Vector2(distanceCorner * cos(rb2_rotation + 3 * PI/4), distanceCorner * sin(rb2_rotation +3 * PI/4)));
    //top right
    corners2[2] = Vector2(rb2.getPosition() + Vector2(distanceCorner * cos(rb2_rotation + PI/4), distanceCorner * sin(rb2_rotation + PI/4)));
    //bottom right
    corners2[3] = Vector2(rb2.getPosition() + Vector2(distanceCorner * cos(rb2_rotation - PI/4), distanceCorner * sin(rb2_rotation - PI/4)));



    //projection and SAT check with c1 and c2 of rb1
    //create axis -> need to check every edge of both shapes
    
    if (!checkAxes(corners1,corners2, corners1[0] - corners1[1])) return false;
    if (!checkAxes(corners1,corners2, corners1[0] - corners1[3])) return false;
    if (!checkAxes(corners1,corners2, corners2[0] - corners2[1])) return false;
    if (!checkAxes(corners1,corners2, corners2[0] - corners2[3])) return false;


    return true;
}