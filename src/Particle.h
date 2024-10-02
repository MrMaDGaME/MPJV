#pragma once

#include "Vector.h"
#include <vector>
#include "ofMain.h"

class Particle {
public:
    Particle();
    Particle(float x, float y, float z);
    Particle(float x, float y, float z, float radius, float mass);
    ~Particle();

    Vector position;
    Vector velocity;

    Vector AccumForce; 

    float inv_mass;
    float radius;
    ofColor color;

    void update();
    void draw();

    void addForce(const& Vector Force);
    void clearAccum();
};
