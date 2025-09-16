#pragma once
#include "Utilities.h"
#include <iostream>
#include <utility>
#include <numbers>
#include <memory>

class Shape {
    public:
    virtual ~Shape() = default;
    virtual float computeMomentInertia(float mass) const = 0;
    virtual void draw() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void print(std::ostream &o) const = 0;
    friend std::ostream &operator<<(std::ostream &out, const Shape shape);
};
std::ostream &operator<<(std::ostream &out, const Shape &shape);

class Circle : public Shape {
    float radius;
    public:
    
    std::unique_ptr<Shape> clone() const override;

    float getRadius() const;
    void setRadius(float r);
    float computeMomentInertia(float mass) const override;
    void draw() const override;
    void print(std::ostream &o) const override;
    Circle();
    Circle(float radius);
};

class Rectangle : public Shape {
    float width, height;
    public: 

    std::unique_ptr<Shape> clone() const override;
    float getWidth() const;
    float getHeight() const;
    void setWidth(float w);
    void setHeight(float h);
    float computeMomentInertia(float mass) const override;
    void draw() const override;
    void print(std::ostream &o) const override;
    Rectangle();
    Rectangle(float w, float h);
};

class Entity {
    friend std::ostream &operator<<(std::ostream &out, const Entity &e);
    
    protected:
    Vector2 position;

    public:
    float rotation = 0.0f;
    
    Entity(const Vector2 position);
    void setPosition(const Vector2 &v);
    Vector2 getPosition() const;

};
std::ostream &operator<<(std::ostream &out, const Entity &e);

class RigidBody : public Entity {
    void swap(RigidBody &rb);
    
    friend std::ostream &operator<<(std::ostream &out, const RigidBody &rb);
    
    protected:
    Vector2 velocity;
    Vector2 acceleration;

    float mass = 1.0f;
    float restitution = 1.0f;
    float staticFriction = 0.0f;
    float dynamicFriction = 0.0f;

    std::unique_ptr<Shape> collider; //unique pointer -> rb owns collider, when rb dies collider dies. Cannot transfer ownser ship (no copy constructor)

    public:

    float momentInertia = 0.0f;
    float angularVelocity = 0.0f;
    float torque = 0.0f;

    void setVelocity(const Vector2 &v);
    Vector2 getVelocity() const;

    void setAcceleration(const Vector2 &a);
    Vector2 getAcceleration() const;

    void setMass(float m);
    float getMass() const;

    void setRestitution(float r);
    float getRestitution() const;

    void setSFriction(float f);
    float getSFriction() const;

    void setDFriction(float d);
    float getDFriction() const;

    void setCollider(std::unique_ptr<Shape> collider);

    RigidBody(std::unique_ptr<Shape> col = nullptr, 
            const Vector2 &pos = Vector2(0,0),
            const Vector2 &vel = Vector2(0,0),
            const Vector2 &acc = Vector2(0,0));
    RigidBody( 
        const Vector2 &pos = Vector2(0,0),
        const Vector2 &vel = Vector2(0,0),
        const Vector2 &acc = Vector2(0,0));
    RigidBody(const Entity &e);
    RigidBody(const RigidBody &rb);
    RigidBody(RigidBody &&rb);


    RigidBody &operator=(const RigidBody &rb);
    RigidBody &operator=(RigidBody &&rb);

};
std::ostream &operator<<(std::ostream &out, const RigidBody &rb);

