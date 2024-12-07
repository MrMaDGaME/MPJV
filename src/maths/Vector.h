#pragma once
#include <math.h>

class Vector {
public:
    Vector();
    Vector(float x, float y);
    Vector(float x, float y, float z);

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(float s) const;
    Vector operator/(float s) const;
    Vector operator+=(const Vector& v);
    Vector operator-=(const Vector& v);
    Vector operator*=(float s);
    Vector operator/=(float s);
    float operator*(const Vector& v) const;
    Vector operator^(const Vector& v) const;
    float magnitude() const;
    Vector& normalize();
    [[nodiscard]] Vector getNormal() const;
    Vector limit(float max);
    float distance(const Vector& v) const;
    float angle(const Vector& v) const;
    Vector rotate(float angle) const;
    Vector lerp(const Vector& v, float t);
    Vector slerp(const Vector& v, float t);
    Vector nlerp(const Vector& v, float t);
    Vector project(const Vector& v);
    Vector reject(const Vector& v);
    Vector reflect(const Vector& v);
    Vector refract(const Vector& v, float eta);
    Vector operator-() const;
    bool operator==(const Vector& v) const;
    bool operator!=(const Vector& v) const;
    bool operator<(const Vector& v) const;
    bool operator>(const Vector& v) const;
    bool operator<=(const Vector& v) const;
    bool operator>=(const Vector& v) const;
    bool operator!() const;
    Vector cross(const Vector& v) const;
    float dot(const Vector& v) const;

    float x;
    float y;
    float z;
};
