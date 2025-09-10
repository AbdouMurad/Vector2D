#include "Utilities.h"
#include "Physics.h"

#include <iostream>

int main() {
    Entity e = Entity(Vector2(1.5, 2));
    std::cout << e << std::endl;

    Vector2 v = e.getPosition();
    v.x = 10;
    std::cout << e << std::endl;
}