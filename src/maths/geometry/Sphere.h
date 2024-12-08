#pragma once

#include "../Vector.h"

class Sphere {
public:
    Sphere(Vector center, float radius);

    [[nodiscard]] const Vector& getCenter() const;
    [[nodiscard]] float getRadius() const;

    bool IsOverlaping(Sphere& other);

protected:
    Vector center_;
    float radius_;
};
