#pragma once
#include "../Box.h"
#define COREBOX_HEIGHT 70.f
#define COREBOX_WIDTH 60.f
#define COREBOX_DEPTH 40.f
#define COREBOX_MASS 1.f
#define COREBOX_CORERADIUS 10.f
#define COREBOX_COLOR ofColor::lime

class CoreBox : public Box {
public :
    CoreBox(float x, float y, float z) : Box(x,
                                             y,
                                             z,
                                             COREBOX_HEIGHT,
                                             COREBOX_WIDTH,
                                             COREBOX_DEPTH,
                                             COREBOX_MASS,
                                             computeInertia(COREBOX_MASS, COREBOX_CORERADIUS),
                                             COREBOX_COLOR) {
    }

private :
    static Matrix3x3 computeInertia(float mass, float coreradius) {
        float mat[3][3] = {
            {2.f / 5 * mass * coreradius * coreradius, 0, 0}, {0, 2.f / 5 * mass * coreradius * coreradius, 0},
            {0, 0, 2.f / 5 * mass * coreradius * coreradius}
        };
        return Matrix3x3(mat);
    }
};
