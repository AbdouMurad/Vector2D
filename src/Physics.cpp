#include "Physics.h"


Entity::~Entity() {
    delete position;
}
Entity::Entity(): position(new Vector2()), rotation(0) {}
Entity::Entity(const Vector2 &v): position(new Vector2(v)), rotation(0) {} 
Entity::Entity(const Entity &e): position(new Vector2(*e.position)), rotation(e.rotation) {}

void Entity::setPosition(const Vector2 &v) {
    position = new Vector2(v);
}
Vector2 Entity::getPosition() const{
    return *position;
}

std::ostream &operator<<(std::ostream &out, const Entity &other) {
    return out << "[Position: " << *other.position << "," << "Rotation: " << other.rotation << "]"; 
}