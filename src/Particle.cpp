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

    float last_frame = static_cast<float>(ofGetLastFrameTime());
    velocity += AccumForce * last_frame;
    position += (velocity * last_frame + (AccumForce * last_frame * last_frame) / 2) * 100; // Passage en cm
}

void Particle::draw() {
    ofSetColor(color);

    ofDrawSphere(position.x, position.y, position.z, radius);
}
