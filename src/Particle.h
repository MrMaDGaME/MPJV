#pragma once

#include "Vector.h"
#include "ofApp.h"

class Particle {
public:
    Particle();
    Particle(float x, float y, float z);
    Particle(float x, float y, float z, float radius, float mass);
    ~Particle();

    Vector position;
    Vector velocity;
    std::vector<std::pair<Vector, float>> accelerations;

    float mass;
    float radius;

    void update();
    void draw();
    void applyForce(float fx, float fy, float fz, float duration);
    void applyForce(float fx, float fy, float duration);
    void applyForce(float fx, float duration);
    void applyForce(Vector force, float duration);
};
