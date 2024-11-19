#pragma once
#include "../Box.h"

class CoreBox : Box {
private :
    float height = 70;
    float width = 60;
    float depth = 40;
    float mass = 10;
    float coreradius = 10;
    ofColor color = ofColor::lime;
public :
    CoreBox(float x, float y, float z) : Box( x,  y,  z, height, width, depth,  mass,  computeInertia(height, width, depth, mass, coreradius), color){}
private :
    static Matrix3x3 computeInertia(float height, float width, float depth, float mass, float coreradius){
        float mat[3][3] ={
            {2/5 * mass*coreradius*coreradius,0,0},
            {0,2/5*mass*coreradius*coreradius,0},
            {0,0,2/5*mass*coreradius*coreradius}};
        return Matrix3x3(mat);
    }


};