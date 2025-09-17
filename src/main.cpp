#include "Utilities.h"
#include "RigidBody.h"
#include <iostream>

int main() {
    std::vector<std::unique_ptr<RigidBody>> array;
    array.push_back(std::make_unique<RigidBody>(std::make_unique<Circle>()));

    std::cout << *array[0] << std::endl;
}