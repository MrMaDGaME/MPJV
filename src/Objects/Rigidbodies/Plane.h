#pragma once
#include "RigidBody.h"

class Plane : public RigidBody, public std::enable_shared_from_this<Plane> {
public:
    Plane(float x, float y, float z, float width, float height);
    Plane(float x, float y, float z, float width, float height, const ofColor& color);
    Plane(const Vector& position, float width, float height);
    Plane(const Vector& position, float width, float height, const ofColor& color);
    Plane(const Vector& position, float width, float height, const Quaternion& rotation, const ofColor& color);
    Plane(const std::vector<glm::vec3>& corners);

    void draw() override;
    void update() override;
    void rotate(const Quaternion& rot_quat) override;
    void set_corners();
    void set_normal();
    [[nodiscard]] float get_width() const;
    [[nodiscard]] float get_height() const;
    [[nodiscard]] const Vector& get_normal() const;
    [[nodiscard]] const std::vector<glm::vec3>& get_corners() const;

    float checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const override;
    float checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const override;
    float checkCollisionWithBox(const std::shared_ptr<const Box>& box) const override;

    [[nodiscard]] const Sphere& get_bounding_sphere() const override;

protected:
    float width_, height_;
    Vector normal_;
    std::vector<glm::vec3> corners_ = std::vector<glm::vec3>(4);
    Sphere bounding_sphere_;
};
