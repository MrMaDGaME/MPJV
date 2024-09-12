#include "Particle.h"
#include <iostream>

Particle::Particle() {
    position = Vector(0, 0, 0);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    mass = 1;
    radius = 10;
}

Particle::Particle(const float x, const float y, const float z) {
    position = Vector(x, y, z);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    mass = 1;
    radius = 10;
}

Particle::Particle(const float x, const float y, const float z, const float radius, const float mass) {
    position = Vector(x, y, z);
    velocity = Vector(0, 0, 0);
    acceleration = Vector(0, 0, 0);
    this->mass = mass;
    this->radius = radius;
}

Particle::~Particle() {
}

void Particle::update() {
    // std::cout << "acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << std::endl;
    velocity += acceleration;
    position += velocity;
    acceleration *= 0;
}

void Particle::draw() {
    ofDrawSphere(position.x, position.y, position.z, radius);
}

void Particle::applyForce(float fx, float fy, float fz) {
    Vector force = Vector(fx, fy, fz);
    applyForce(force);
}

void Particle::applyForce(float fx, float fy) {
    applyForce(fx, fy, 0);
}

void Particle::applyForce(float fx) {
    applyForce(fx, 0, 0);
}

void Particle::applyForce(Vector force) {
    Vector f = force / mass;
    acceleration += f;
    std::cout << "acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << std::endl;
}
