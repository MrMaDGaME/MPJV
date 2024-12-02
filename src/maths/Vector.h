#pragma once
#include <math.h>

class Vector {
public:
    Vector();
    Vector(float x, float y);
    Vector(float x, float y, float z);
    ~Vector();

    Vector operator+(Vector v);
    Vector operator-(Vector v);
    Vector operator*(float s);
    Vector operator/(float s);
    Vector operator+=(Vector v);
    Vector operator-=(Vector v);
    Vector operator*=(float s);
    Vector operator/=(float s);
    float operator*(Vector v);
    Vector operator^(Vector v);
    float magnitude() const;
    Vector normalize();
    Vector limit(float max);
    float distance(Vector v);
    float angle(Vector v);
    Vector rotate(float angle);
    Vector lerp(Vector v, float t);
    Vector slerp(Vector v, float t);
    Vector nlerp(Vector v, float t);
    Vector project(Vector v);
    Vector reject(Vector v);
    Vector reflect(Vector v);
    Vector refract(Vector v, float eta);
    Vector operator-();
    bool operator==(Vector v);
    bool operator!=(Vector v);
    bool operator<(Vector v);
    bool operator>(Vector v);
    bool operator<=(Vector v);
    bool operator>=(Vector v);
    bool operator!();
    Vector cross(const Vector& v) const;
    float dot(const Vector& v) const;

    float x;
    float y;
    float z;
};
