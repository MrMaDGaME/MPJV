#include "Vector.h"

Vector::Vector() {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(const float x, const float y) {
    this->x = x;
    this->y = y;
    z = 0;
}

Vector::Vector(const float x, const float y, const float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(const float s) const {
    return Vector(x * s, y * s, z * s);
}

Vector Vector::operator/(const float s) const {
    return Vector(x / s, y / s, z / s);
}

Vector Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector Vector::operator*=(const float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vector Vector::operator/=(const float s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}

bool Vector::operator==(const Vector& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator!=(const Vector& v) const {
    return x != v.x || y != v.y || z != v.z;
}

bool Vector::operator<(const Vector& v) const {
    return x < v.x && y < v.y && z < v.z;
}

bool Vector::operator>(const Vector& v) const {
    return x > v.x && y > v.y && z > v.z;
}

bool Vector::operator<=(const Vector& v) const {
    return x <= v.x && y <= v.y && z <= v.z;
}

bool Vector::operator>=(const Vector& v) const {
    return x >= v.x && y >= v.y && z >= v.z;
}

bool Vector::operator!() const {
    return x == 0 && y == 0 && z == 0;
}

Vector Vector::cross(const Vector& v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

float Vector::dot(const Vector& v) const {
    return x * v.x + y * v.y + z * v.z;
}

float Vector::operator*(const Vector& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator^(const Vector& v) const {
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

Vector& Vector::normalize() {
    float m = magnitude();
    if (m > 0) {
        x /= m;
        y /= m;
        z /= m;
    }
    return *this;
}

Vector Vector::getNormal() const {
    float m = magnitude();
    if (m > 0) {
        return {x / m, y / m, z / m};
    }
    return {};
}

Vector Vector::limit(const float max) {
    if (magnitude() > max) {
        normalize();
        *this *= max;
    }
    return *this;
}

float Vector::distance(const Vector& v) const {
    return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
}

float Vector::angle(const Vector& v) const {
    return acos((*this * v) / (magnitude() * v.magnitude()));
}

Vector Vector::rotate(const float angle) const {
    float s = sin(angle);
    float c = cos(angle);
    return Vector(x * c - y * s, x * s + y * c, z);
}

Vector Vector::lerp(const Vector& v, const float t) {
    return *this + (v - *this) * t;
}

Vector Vector::slerp(const Vector& v, const float t) {
    float theta = angle(v);
    float sinTheta = sin(theta);
    return *this * sin((1 - t) * theta) / sinTheta + v * sin(t * theta) / sinTheta;
}

Vector Vector::nlerp(const Vector& v, const float t) {
    return lerp(v, t).normalize();
}

Vector Vector::project(const Vector& v) {
    return v * (*this * v) / (v * v);
}

Vector Vector::reject(const Vector& v) {
    return *this - project(v);
}

Vector Vector::reflect(const Vector& v) {
    return *this - v * 2 * (*this * v) / (v * v);
}

Vector Vector::refract(const Vector& v, const float eta) {
    float cosI = -(*this * v);
    float sinT2 = eta * eta * (1 - cosI * cosI);
    if (sinT2 > 1) {
        return {};
    }
    float cosT = sqrt(1 - sinT2);
    return *this * eta + v * (eta * cosI - cosT);
}
