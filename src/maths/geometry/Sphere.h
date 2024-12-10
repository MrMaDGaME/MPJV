#pragma once

#include "../Vector.h"

class Sphere {
public:
    Sphere(Vector center, float radius);

    [[nodiscard]] const Vector& getCenter() const;
    [[nodiscard]] float getRadius() const;
    void set_center(const Vector& center);

    bool IsOverlaping(Sphere& other);

protected:
    Vector center_;
    float radius_;
};
