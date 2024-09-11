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

Vector::~Vector() {
}

Vector Vector::operator+(Vector v) {
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v) {
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float s) {
	return Vector(x * s, y * s, z * s);
}

Vector Vector::operator/(float s) {
	return Vector(x / s, y / s, z / s);
}

Vector Vector::operator+=(Vector v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector Vector::operator-=(Vector v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector Vector::operator*=(float s) {
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector Vector::operator/=(float s) {
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector Vector::operator-() {
	return Vector(-x, -y, -z);
}

bool Vector::operator==(Vector v) {
	return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator!=(Vector v) {
	return x != v.x || y != v.y || z != v.z;
}

bool Vector::operator<(Vector v) {
	return x < v.x && y < v.y && z < v.z;
}

bool Vector::operator>(Vector v) {
	return x > v.x && y > v.y && z > v.z;
}

bool Vector::operator<=(Vector v) {
	return x <= v.x && y <= v.y && z <= v.z;
}

bool Vector::operator>=(Vector v) {
	return x >= v.x && y >= v.y && z >= v.z;
}

bool Vector::operator!() {
	return x == 0 && y == 0 && z == 0;
}

float Vector::operator*(Vector v) {
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator^(Vector v) {
	return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float Vector::magnitude() {
	return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() {
	float m = magnitude();
	if (m != 0) {
		x /= m;
		y /= m;
		z /= m;
	}
	return *this;
}

Vector Vector::limit(float max) {
	if (magnitude() > max) {
		normalize();
		*this *= max;
	}
	return *this;
}

float Vector::distance(Vector v) {
	return sqrt(pow(x - v.x, 2) + pow(y - v.y, 2) + pow(z - v.z, 2));
}

float Vector::angle(Vector v) {
	return acos((*this * v) / (magnitude() * v.magnitude()));
}

Vector Vector::rotate(float angle) {
	float s = sin(angle);
	float c = cos(angle);
	return Vector(x * c - y * s, x * s + y * c, z);
}

Vector Vector::lerp(Vector v, float t) {
	return *this + (v - *this) * t;
}

Vector Vector::slerp(Vector v, float t) {
	float theta = angle(v);
	float sinTheta = sin(theta);
	return *this * sin((1 - t) * theta) / sinTheta + v * sin(t * theta) / sinTheta;
}

Vector Vector::nlerp(Vector v, float t) {
	return lerp(v, t).normalize();
}

Vector Vector::project(Vector v) {
	return v * (*this * v) / (v * v);
}

Vector Vector::reject(Vector v) {
	return *this - project(v);
}

Vector Vector::reflect(Vector v) {
	return *this - v * 2 * (*this * v) / (v * v);
}

Vector Vector::refract(Vector v, float eta) {
	float cosI = -(*this * v);
	float sinT2 = eta * eta * (1 - cosI * cosI);
	if (sinT2 > 1) {
		return Vector();
	}
	float cosT = sqrt(1 - sinT2);
	return *this * eta + v * (eta * cosI - cosT);
}
