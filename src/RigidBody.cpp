#include "RigidBody.h"

Entity::Entity(const Vector2 pos) 
    :   position(pos)
    {}
void Entity::setPosition(const Vector2 &v) {
    position = v;
}
Vector2 Entity::getPosition() const{
    return position;
}
double Entity::getRotation() const {
    return rotation;
}
void Entity::setRotation(double r) {
    if (r > PI) {
        r -= 2*PI * ceil(r/(2*PI));
    }
    else if (r < PI) {
        r -= 2*PI*floor(r/(2*PI));
    }
    rotation = r;
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
    std::swap(forces, rb.forces);
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
            const Vector2 &acc,
            const Vector2 &force) 
    :   Entity(pos),
        velocity(vel),
        acceleration(acc),
        forces(force),
        collider(std::move(col)) {
            if (collider) {
                momentInertia = collider->computeMomentInertia(mass);
            }
        }
RigidBody::RigidBody(            
            const Vector2 &pos,
            const Vector2 &vel,
            const Vector2 &acc,
            const Vector2 &force) 
    :   Entity(pos),
        velocity(vel),
        acceleration(acc),
        forces(force),
        collider(nullptr) {}
RigidBody::RigidBody(const Entity &e)
    :   Entity(e), 
        velocity(Vector2()), 
        acceleration(Vector2()),
        forces(Vector2()) {}
RigidBody::RigidBody(const RigidBody &rb)
    :   Entity(rb), 
        velocity(Vector2(rb.velocity)), 
        acceleration(Vector2(rb.acceleration)),
        forces(Vector2(rb.forces)), 
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
    forces = rb.forces;

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
        recomputeInertia();
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
void RigidBody::recomputeInertia() {
    if (collider) {
        momentInertia = collider->computeMomentInertia(mass);
    }
}
void RigidBody::setCollider(std::unique_ptr<Shape> col) {
    collider = std::move(col);
    recomputeInertia();
}
void RigidBody::applyForce(const Vector2 &force) {
    forces += force;
}
void RigidBody::integrate(float dt) {
    acceleration = forces/mass;
    velocity += acceleration * dt;
    position += velocity *dt;
    forces = Vector2();
}
bool RigidBody::hasCollider() const {
    return collider ? true : false;
}
float RigidBody::getSize() const {
    if (collider) {
        return collider->getSize();
    }
    else {
        return 0;
    }
}
Shape *RigidBody::getCollider() const {
    return collider.get();
}

std::ostream &operator<<(std::ostream &out, const RigidBody &rb) {
    out << "RigidBody : {\n"
    << "        [Position: " << rb.position << "," << "Rotation: " << rb.rotation << "],\n"
    << "        Velocity: " << rb.velocity << ",\n"
    << "        Acceleration: " << rb.acceleration << ",\n" 
    << "        Mass: " << rb.mass << ",\n"
    << "        Restitution: " << rb.restitution << ",\n"
    << "        Static Friction: " << rb.staticFriction << ",\n"
    << "        Dynamic Friction: " << rb.dynamicFriction << ",\n"
    << "        Moment of Inertia: " << rb.momentInertia << ",\n"
    << "        Angular Velocity: " << rb.angularVelocity << ",\n"
    << "        Torque: " << rb.torque << ",\n"
    << "        Collider: ";
    if (rb.collider) {
        out << *rb.collider;
    }
    else {
        out << "{NONE}";
    }
    return out << "\n}" << std::endl;
}

std::ostream &operator<<(std::ostream &o, const Shape &shape){
    shape.print(o);
    return o;
}

std::unique_ptr<Shape> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

Circle::Circle()
    :   radius(0.5) {}
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
void Circle::draw() const {
    std::cout << "Drawing Circle..." << std::endl;
}
void Circle::print(std::ostream &o) const {
    o << "{Shape : 'Circle', Radius: " << radius << "}";
}
float Circle::getSize() const {
    return radius;
}
std::unique_ptr<Shape> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}
Rectangle::Rectangle()
    :   width(1),
        height(1) {}
Rectangle::Rectangle(float w, float h)
    :   width(w),
        height(h) {}
float Rectangle::computeMomentInertia(float mass) const {
    return mass * (width * width + height * height) /12;
}
float Rectangle::getWidth() const {
    return width;
}
float Rectangle::getHeight() const {
    return height;
}
void Rectangle::setWidth(float w) {
    if (w > 0) {
        width = w;
    }
    else {
        std::cerr << "ERROR: WIDTH SET LESS THAN OR EQUAL TO ZERO" << std::endl;
    }
} 
void Rectangle::setHeight(float h) {
    if (h > 0) {
        height = h;
    }
    else {
        std::cerr << "ERROR: HEIGHT SET LESS THAN OR EQUAL TO ZERO" << std::endl;
    }
}
void Rectangle::draw() const {
    std::cout << "Printing Rectangle..." << std::endl;
}
void Rectangle::print(std::ostream &out) const {
    out << "{Shape: 'Rectangle', Height: " << height << ", Width: " << width << "}";
}
float Rectangle::getSize() const {
    return max(width, height);
}