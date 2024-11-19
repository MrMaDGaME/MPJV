#pragma once
#include "../Box.h"
#define UNIFORM_HEIGHT 75.f
#define UNIFORM_WIDTH 20.f
#define UNIFORM_DEPTH 50.f
#define UNIFORM_MASS 1.f
#define UNIFORM_CORERADIUS 10.f
#define UNIFORM_COLOR ofColor::coral

class UniformBox : public Box {
public :
    UniformBox(float x, float y, float z) : Box( x,  y,  z, UNIFORM_HEIGHT, UNIFORM_WIDTH, UNIFORM_DEPTH,  UNIFORM_MASS,  computeInertia(UNIFORM_HEIGHT, UNIFORM_WIDTH, UNIFORM_DEPTH, UNIFORM_MASS), UNIFORM_COLOR){}
private :
    static Matrix3x3 computeInertia(float height, float width, float depth, float mass){
        float mat[3][3] ={
            {1.f/12 * mass*(height*height+depth*depth),0,0},
            {0,1.f/12*mass*(width*width + height*height),0},
            {0,0,1.f/12*mass*(width*width + depth *depth)}};
        return Matrix3x3(mat);
    }


};