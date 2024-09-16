#pragma once 

#include "../Particle.h"
#define BULLET_RADIUS 10.f
#define BULLET_MASS 10.f

class Bullet : public Particle {
public:

    Bullet(float x, float y, float z) : Particle(x,y,z,BULLET_RADIUS,BULLET_MASS){};

    void draw(){
        ofSetColor(ofColor::lightGray);

        ofDrawSphere(position.x, position.y, position.z, radius);

    };
};