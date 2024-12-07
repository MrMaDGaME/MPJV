#pragma once
#include "RigidBody.h"

class Plane : public RigidBody, public std::enable_shared_from_this<Plane> {
public:
    Plane(float x, float y, float z, float width, float height, const Vector& normal);
    Plane(float x, float y, float z, float width, float height, const Vector& normal, const ofColor& color);
    Plane(const Vector& position, float width, float height, const Vector& normal);
    Plane(const Vector& position, float width, float height, const Vector& normal, const ofColor& color);

    void draw() override;
    void update() override;
    void rotate(const Quaternion& rot_quat) override;
    [[nodiscard]] float get_width() const;
    [[nodiscard]] float get_height() const;
    [[nodiscard]] const Vector& get_normal() const;

    static Quaternion normalToQuat(const Vector& normal);
    static Vector quatToNormal(const Quaternion& quat);

    float checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const override;
    float checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const override;
    float checkCollisionWithBox(const std::shared_ptr<const Box>& box) const override;

protected:
    float width_, height_;
    Vector normal_;
};
