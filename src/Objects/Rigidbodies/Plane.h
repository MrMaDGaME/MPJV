#pragma once
#include "RigidBody.h"

class Plane : public RigidBody {
public:
    Plane(float x, float y, float z, float width, float height, const Vector& normal);
    Plane(float x, float y, float z, float width, float height, const Vector& normal, const ofColor& color);
    Plane(const Vector& position, float width, float height, const Vector& normal);
    Plane(const Vector& position, float width, float height, const Vector& normal, const ofColor& color);

    void draw() override;
    void update() override;
    void rotate(const Quaternion& rot_quat) override;

    static Quaternion normalToQuat(const Vector& normal);
    static Vector quatToNormal(const Quaternion& quat);

protected:
    float width_, height_;
    Vector normal_;
};
