#include "Physics.h"


Entity::Entity(const Vector2 pos) 
    :   position(pos)
    {}
void Entity::setPosition(const Vector2 &v) {
    position = v;
}
Vector2 Entity::getPosition() const{
    return position;
}
std::ostream &operator<<(std::ostream &out, const Entity &other) {
    return out << "[Position: " << other.position << "," << "Rotation: " << other.rotation << "]"; 
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
    std::swap(collider, rb.collider);
}

RigidBody::RigidBody(std::unique_ptr<Shape> col,            
            const Vector2 &pos,
            const Vector2 &vel,
            const Vector2 &acc) 
    :   Entity(pos),
        velocity(vel),
        acceleration(acc),
        collider(std::move(col)) {}
RigidBody::RigidBody(const Entity &e)
    :   Entity(e), 
        velocity(Vector2()), 
        acceleration(Vector2()) {}
RigidBody::RigidBody(const RigidBody &rb)
    :   Entity(rb), 
        velocity(Vector2(rb.velocity)), 
        acceleration(Vector2(rb.acceleration)), 
        mass(rb.mass), 
        momentInertia(rb.momentInertia), 
        angularVelocity(rb.angularVelocity), 
        torque(rb.torque), 
        restitution(rb.restitution), 
        staticFriction(rb.staticFriction), 
        dynamicFriction(rb.dynamicFriction),
        collider(rb.collider ? rb.collider->clone() : nullptr) {}

RigidBody &RigidBody::operator=(const RigidBody &rb){
    if (this == &rb) return *this;
    position = rb.position;
    velocity = rb.velocity;
    acceleration = rb.acceleration;

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
void RigidBody::setVelocity(const Vector2 &vector) {
    velocity = vector;
}
Vector2 RigidBody::getVelocity() const {
    return velocity;
}
void RigidBody::setAcceleration(const Vector2 &vector) {
    acceleration = vector;
}
Vector2 RigidBody::getAcceleration() const {
    return acceleration;
}
void RigidBody::setMass(float value) {
    if (value > 0) {
        mass = value;
    }
    else {
        std::cerr << "ERROR: MASS SET BELOW ZERO" << std::endl;
    }
}
float RigidBody::getMass() const {
    return mass;
}
void RigidBody::setRestitution(float value) {
    if (value >= 0 && value <= 1) {
        restitution = value;
    }
    else
    {
        std::cerr << "ERROR: RIGIDBODY RESTITUTION OUTSIDE OF [0,1]" << std::endl;
    }
}
float RigidBody::getRestitution() const {
    return restitution;
}
void RigidBody::setSFriction(float value) {
    if (value >= 0) {
        staticFriction = value;
    }
    else {
        std::cerr << "ERROR: STATIC FRICTION SET BELOW ZERO" << std::endl;
    }
}
float RigidBody::getSFriction() const {
    return staticFriction;
}
void RigidBody::setDFriction(float value) {
    if (value >= 0) {
        dynamicFriction = value;
    }
    else {
        std::cerr << "ERROR: DYNAMIC FRICTION SET BELOW ZERO" << std::endl;
    }
}
float RigidBody::getDFriction() const {
    return dynamicFriction;
}
std::ostream &operator<<(std::ostream &out, const RigidBody &rb) {
    return out << "[Position: " << rb.position << ", Velocity: " << rb.velocity << ", Acceleration: " << rb.acceleration << "," 
    << std::endl << "Mass: " << rb.mass << ", Restitution: " << rb.restitution << ", Static Friction: " << rb.staticFriction << ", Dynamic Friction: " 
    << rb.dynamicFriction <<  std::endl << "Moment of Inertia: " << rb.momentInertia << ", Angular Velocity: " << rb.angularVelocity << ", Torque: " << rb.torque << std::endl << *rb.collider << "]" << std::endl;  
}

std::ostream &operator<<(std::ostream &o, const Shape &shape){
    shape.print(o);
    return o;
}

std::unique_ptr<Shape> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

Circle::Circle()
    :   radius(1.0) {}
Circle::Circle(float r)
    :   radius(r) {}

float Circle::computeMomentInertia(float mass) const {
    return 0.5f * mass * radius * radius;
}
float Circle::getRadius() const {
    return radius;
}
void Circle::setRadius(float r) {
    if (r > 0) {
        radius = r;
    }
    else {
        std::cerr << "ERROR: RADIUS SET LESS THAN OR EQUAL TO ZERO" << std::endl;
    }
}
void Circle::draw() {
    std::cout << "Printing" << std::endl;
}
void Circle::print(std::ostream &o) const {
    o << "{Shape : 'Circle', Radius: << " << radius << "}";
}
