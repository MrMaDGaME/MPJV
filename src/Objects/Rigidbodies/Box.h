#pragma once
#include "RigidBody.h"

class Box : public RigidBody, public std::enable_shared_from_this<Box> {
public:
    Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia);
    Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color);
    Box(const Vector& position, float height, float width, float depth, ofColor color);

    void draw() override;
    void set_bounding_sphere_position() override;
    void set_corners() override;
    [[nodiscard]] float get_width() const;
    [[nodiscard]] float get_height() const;
    [[nodiscard]] float get_depth() const;
    [[nodiscard]] const std::vector<glm::vec3>& get_corners() const;

    float checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const override;
    float checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const override;
    float checkCollisionWithBox(const std::shared_ptr<const Box>& box) const override;

    [[nodiscard]] const Sphere& get_bounding_sphere() const override;

protected:
    float width_;
    float height_;
    float depth_;
    std::vector<glm::vec3> corners_ = std::vector<glm::vec3>(8);
    Sphere bounding_sphere_;
};
