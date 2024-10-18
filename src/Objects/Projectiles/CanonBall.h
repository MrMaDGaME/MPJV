#pragma once
#include "../Particle.h"
#define CANONBALL_RADIUS 30.f
#define CANONBALL_MASS 50.f

class CanonBall : public Particle {
public:
    CanonBall(float x, float y, float z) : Particle(x, y, z,CANONBALL_RADIUS,CANONBALL_MASS) {
        color_ = ofColor::darkGray;
    }
};
