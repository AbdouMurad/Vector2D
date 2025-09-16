#include "Utilities.h"
#include "Physics.h"
#include <iostream>

int main() {
    auto circCollider = std::make_unique<Rectangle>();
    RigidBody rb(
        //std::move(circCollider),
        Vector2(0,0),
        Vector2(1,0),
        Vector2()
    );
    rb.setRestitution(1);
    std::cout << rb;

    rb.setCollider(std::move(circCollider));
    std::cout << rb;

}