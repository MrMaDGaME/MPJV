#pragma once
#include "../Box.h"

class UniformBox : Box {
private :
    float height = 75;
    float width = 50;
    float depth = 50;
    float mass = 10;
    ofColor color = ofColor::lime;
public :
    UniformBox(float x, float y, float z) : Box( x,  y,  z, height, width, depth,  mass,  computeInertia(height, width, depth, mass), color){}
private :
    static Matrix3x3 computeInertia(float height, float width, float depth, float mass){
        float mat[3][3] ={
            {1/12 * mass*(height*height+depth*depth),0,0},
            {0,1/12*mass*(width*width + height*height),0},
            {0,0,1/12*mass*(width*width + depth *depth)}};
        return Matrix3x3(mat);
    }


};