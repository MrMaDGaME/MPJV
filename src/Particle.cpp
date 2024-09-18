#include "Particle.h"
#include <iostream>

Particle::Particle() {
    position = Vector(0, 0, 0);
    velocity = Vector(0, 0, 0);
    inv_mass = 1;
    radius = 10;
}

Particle::Particle(const float x, const float y, const float z) {
    position = Vector(x, y, z);
    velocity = Vector(0, 0, 0);
    inv_mass = 1;
    radius = 10;
}

Particle::Particle(const float x, const float y, const float z, const float radius, const float mass) {
    position = Vector(x, y, z);
    velocity = Vector(0, 0, 0);
    this->inv_mass = mass != 0 ? 1 / mass : 0;
    this->radius = radius;
}

Particle::~Particle() {
}

void Particle::update() {
    Vector total_acceleration(0, 0, 0);
    for (auto& a : accelerations) {
        total_acceleration += a.first;
        a.second -= ofGetLastFrameTime();
    }
    float last_frame = static_cast<float>(ofGetLastFrameTime());
    ofRemove(accelerations, [](std::pair<Vector, float>& a) { return a.second < 0; });
    velocity += total_acceleration * last_frame;
    position += (velocity * last_frame + (total_acceleration * last_frame * last_frame) / 2) * 100; // Passage en cm
}

void Particle::draw() {
    ofSetColor(color);

    ofDrawSphere(position.x, position.y, position.z, radius);
}

void Particle::applyForce(float fx, float fy, float fz, float duration) {
    Vector force = Vector(fx, fy, fz);
    applyForce(force, duration);
}

void Particle::applyForce(float fx, float fy, float duration) {
    applyForce(fx, fy, 0, duration);
}

void Particle::applyForce(float fx, float duration) {
    applyForce(fx, 0, 0, duration);
}

void Particle::applyForce(Vector force, float duration) {
    accelerations.emplace_back(force * inv_mass, duration);
}
