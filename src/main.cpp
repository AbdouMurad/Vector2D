#include "Utilities.h"
#include "Physics.h"
#include <iostream>

int main() {
    auto circCollider = std::make_unique<Circle>(3.0f);
    RigidBody rb(
        std::move(circCollider),
        Vector2(0,0),
        Vector2(1,0),
        Vector2()
    );

    std::cout << rb;

    rb.setMass(10);
    std::cout << rb;
}