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
    Vector acceleration;

    float mass;
    float radius;

    void update();
    void draw();
    void applyForce(float fx, float fy, float fz);
    void applyForce(float fx, float fy);
    void applyForce(float fx);
    void applyForce(Vector force);
};
