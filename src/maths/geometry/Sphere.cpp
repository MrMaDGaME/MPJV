#include "Sphere.h"

Sphere::Sphere(Vector center, float radius) : center_(center), radius_(radius) {}

const Vector& Sphere::getCenter() const {
    return center_;
}

float Sphere::getRadius() const {
    return radius_;
}

bool Sphere::IsOverlaping(Sphere &other){
    return (center_ - other.getCenter()).magnitude() <= radius_ + other.getRadius();
}
