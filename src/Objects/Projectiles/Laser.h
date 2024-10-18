#pragma once
#include "../Particle.h"
#define LASER_RADIUS 5.f
#define LASER_MASS 1.f

class Laser : public Particle {
public:
    Laser(float x, float y, float z) : Particle(x, y, z,LASER_RADIUS,LASER_MASS) {
        color_ = ofColor::lawnGreen;
    }
};
