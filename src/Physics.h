#pragma once
#include "Utilities.h"
#include <iostream>
#include <utility>

class Entity {
    friend std::ostream &operator<<(std::ostream &out, const Entity &e);
    
    protected:
    Vector2 *position;

    public:
    float rotation = 0.0f;
    
    void setPosition(const Vector2 &v);
    Vector2 getPosition() const;
    
    ~Entity();
    Entity();
    Entity(const Vector2 &v);
    Entity(const Entity &e);
    Entity(Entity &&e);

    Entity &operator=(const Entity &e);
    Entity &operator=(Entity &&e);

};
std::ostream &operator<<(std::ostream &out, const Entity &e);

class RigidBody : public Entity {
    void swap(RigidBody &rb);
    
    friend std::ostream &operator<<(std::ostream &out, const RigidBody &rb);
    
    protected:

    Vector2 *velocity;
    Vector2 *acceleration;

    float mass = 1.0f;
    float momentInertia = 0.0f;

    float angularVelocity = 0.0f;
    float torque = 0.0f;

    float restitution = 1.0f;

    float staticFriction = 0.0f;
    float dynamicFriction = 0.0f;

    public:
    void setVelocity(const Vector2 &v);
    void setAcceleration(const Vector2 &a);
    
    void setMass(float m);
    void setMomentInertia(float i);

    void setAngularVelocity(float a);
    void setTorque(float t);

    void setRestitution(float r);

    void setSFriction(float f);
    void setDFriction(float d);

    ~RigidBody();
    RigidBody();
    RigidBody(const Vector2 &position);
    RigidBody(const Vector2 &position, const Vector2 &velocity);
    RigidBody(const Vector2 &position, const Vector2 &velocity, const Vector2 &acceleration);
    RigidBody(const Entity &e);
    RigidBody(const RigidBody &rb);
    RigidBody(RigidBody &&rb);

    RigidBody &operator=(const RigidBody &rb);
    RigidBody &operator=(RigidBody &&rb);

};
std::ostream &operator<<(std::ostream &out, const RigidBody &rb);