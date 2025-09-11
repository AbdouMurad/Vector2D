#include "Physics.h"


Entity::~Entity() {
    delete position;
}
Entity::Entity()
    :   position(new Vector2()){}
Entity::Entity(const Vector2 &v)
    :   position(new Vector2(v)) {} 
Entity::Entity(const Entity &e)
    :   position(new Vector2(*e.position)), 
        rotation(e.rotation) {}
Entity::Entity(Entity &&e)
    :   position(e.position), 
        rotation(e.rotation) {
    e.position = nullptr;
}
Entity &Entity::operator=(const Entity &e) {
    if (this == &e) return *this;
    delete position;
    position = new Vector2(*e.position);
    rotation = e.rotation;
    return *this;
}
Entity &Entity::operator=(Entity &&e) {
    std::swap(position, e.position); //the destructer of the r-value will be called after this -> we can give it data to clean up for us
    rotation = e.rotation;
    return *this;
}
void Entity::setPosition(const Vector2 &v) {
    delete position;
    position = new Vector2(v);
}
Vector2 Entity::getPosition() const{
    return *position;
}
std::ostream &operator<<(std::ostream &out, const Entity &other) {
    return out << "[Position: " << *other.position << "," << "Rotation: " << other.rotation << "]"; 
}

//RigidBody - Class
void RigidBody::swap(RigidBody &rb) {
    std::swap(position, rb.position);
    std::swap(rotation, rb.rotation);
    std::swap(velocity, rb.velocity);
    std::swap(acceleration, rb.acceleration);
    std::swap(mass, rb.mass);
    std::swap(momentInertia, rb.momentInertia);
    std::swap(angularVelocity, rb.angularVelocity);
    std::swap(torque, rb.torque);
    std::swap(restitution, rb.restitution);
    std::swap(staticFriction, rb.staticFriction);
    std::swap(dynamicFriction, rb.dynamicFriction);
}

RigidBody::~RigidBody() {
    delete velocity;
    delete acceleration;
}
//MOMENT OF INERTIA IS NOT ZERO, MUST CALCULATE FROM SHAPE
RigidBody::RigidBody()
    :   Entity(),
        velocity(new Vector2()),
        acceleration(new Vector2()) {}
RigidBody::RigidBody(const Vector2 &p)
    :   Entity(p),
        velocity(new Vector2()),
        acceleration(new Vector2()) {}
RigidBody::RigidBody(const Vector2 &p, const Vector2 &v) 
    :   Entity(p),
        velocity(new Vector2(v)), 
        acceleration(new Vector2()) {}
RigidBody::RigidBody(const Vector2 &p, const Vector2 &v, const Vector2 &a)
    :   Entity(p), 
        velocity(new Vector2(v)), 
        acceleration(new Vector2(a)) {}
RigidBody::RigidBody(const Entity &e)
    :   Entity(e), 
        velocity(new Vector2()), 
        acceleration(new Vector2()) {}
RigidBody::RigidBody(const RigidBody &rb)
    :   Entity(*rb.position),
        rotation(rb.rotation), 
        velocity(new Vector2(*rb.velocity)), 
        acceleration(new Vector(*rb.acceleration)), 
        mass(rb.mass), 
        momentInertia(rb.momentInertia), 
        angularVelocity(rb.angularVelocity), 
        torque(rb.torque), 
        restitution(rb.restitution), 
        staticFriction(rb.staticFriction), 
        dynamicFriction(rb.dynamicFriction) {}
RigidBody::RigidBody(RigidBody &&rb) 
    :   position(rb.position),
        rotation(rb.rotation), 
        velocity(rb.velocity), 
        acceleration(rb.acceleration), 
        mass(rb.mass), 
        momentInertia(rb.momentInertia), 
        angularVelocity(rb.angularVelocity), 
        torque(rb.torque), restitution(rb.restitution), staticFriction(rb.staticFriction), dynamicFriction(rb.dynamicFriction) {
    rb.position = nullptr;
    rb.velocity = nullptr;
    rb.acceleration = nullptr;
}

RigidBody &RigidBody::operator=(const RigidBody &rb){
    if (this == &rb) return *this;
    delete position;
    delete velocity;
    delete acceleration;
    position = new Vector2(*rb.position);
    velocity = new Vector2(*rb.velocity);
    acceleration = new Vector2(*rb.acceleration);

    mass = rb.mass;
    momentInertia = rb.momentInertia;
    angularVelocity = rb.angularVelocity;
    torque = rb.torque;
    restitution = rb.restitution;
    staticFriction = rb.staticFriction;
    dynamicFriction = rb.dynamicFriction;
    return *this;
}
RigidBody &RigidBody::operator=(RigidBody &&rb) {
    swap(rb);
    return *this;
}