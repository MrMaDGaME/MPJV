#pragma once
#include "RigidBody.h"

class Box : public RigidBody {
public:
    Box(float x, float y, float z, float height, float width, float depth, float mass,float inertia);
    Box(float x, float y, float z, float height, float width, float depth, float mass, float inertia, ofColor color);
    
    void draw() override;
    
protected:
    float width_;
    float height_;
    float depth_;
};
