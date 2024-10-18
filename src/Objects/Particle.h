#pragma once
#include "../maths/Vector.h"
#include "ofMain.h"

class Particle {
public:
    Particle();
    Particle(float x, float y, float z);
    Particle(float x, float y, float z, float radius, float mass);
    Particle(float x, float y, float z, float radius, bool isKinematic);

    void update();
    void draw();
    void addForce(const Vector& Force);
    void clearAccum();

    Vector position;
    Vector velocity;
    Vector AccumForce;
    float inv_mass;
    float radius;
    ofColor color;
};
