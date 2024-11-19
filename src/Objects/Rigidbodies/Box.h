#pragma once
#include "RigidBody.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Box : public RigidBody {
public:
    Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia);
    Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color);
    
    void draw() override;
    
protected:
    float width_;
    float height_;
    float depth_;
};
