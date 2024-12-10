#include "Plane.h"

Plane::Plane(const float x, const float y, const float z, const float width, const float height) : RigidBody(x, y, z), width_(width), height_(height),
                                                                                                   bounding_sphere_(
                                                                                                       position_,
                                                                                                       std::sqrt(
                                                                                                           (width * width + height * height) / 4)) {
}

Plane::Plane(const float x, const float y, const float z, const float width, const float height, const ofColor& color) : RigidBody(x, y, z, color),
    width_(width), height_(height), bounding_sphere_(position_, std::sqrt((width * width + height * height) / 4)) {
}

Plane::Plane(const Vector& position, const float width, const float height) : RigidBody(position), width_(width), height_(height),
                                                                              bounding_sphere_(
                                                                                  position_,
                                                                                  std::sqrt((width * width + height * height) / 4)) {
}

Plane::Plane(const Vector& position, const float width, const float height, const ofColor& color) : RigidBody(position, color), width_(width),
    height_(height), bounding_sphere_(position_, std::sqrt((width * width + height * height) / 4)) {
}

Plane::Plane(const Vector& position, float width, float height, const Quaternion& rotation, const ofColor& color) : Plane(
    position,
    width,
    height,
    color) {
    rotation_ = rotation;
}

Plane::Plane(const std::vector<glm::vec3>& corners) : RigidBody(corners[0] + (corners[2] - corners[0]) / 2), bounding_sphere_({}, 0) {
    corners_ = corners;
    set_normal();
    width_ = glm::distance(corners_[0], corners_[1]);
    height_ = glm::distance(corners_[0], corners_[3]);
}

void Plane::draw() {
    ofSetColor(color_);
    ofPushMatrix();
    for (size_t i = 0; i < 4; ++i) {
        ofDrawLine(corners_[i], corners_[(i + 1) % 4]);
    }
    ofPopMatrix();
}

void Plane::update() {
    RigidBody::update();
    set_normal();
}

void Plane::rotate(const Quaternion& rot_quat) {
    RigidBody::rotate(rot_quat);
    set_normal();
}

void Plane::set_corners() {
    int p = 0;
    for (float i = -0.5; i <= 0.5; i += 1) {
        for (float j = -0.5; j <= 0.5; j += 1) {
            const auto corner = Vector(i * width_, j * height_, 0);
            const auto rotated = rotation_ * Quaternion(0, corner.x, corner.y, corner.z) * rotation_.conjugate();
            corners_[p] = glm::vec3(rotated.x + position_.x, rotated.y + position_.y, rotated.z + position_.z);
            p++;
        }
    }
    // swap corners 2 and 3 to match the correct order
    const auto tmp = corners_[2];
    corners_[2] = corners_[3];
    corners_[3] = tmp;
}

void Plane::set_bounding_sphere_position() {
    bounding_sphere_.set_center(position_);
}

void Plane::set_normal() {
    const auto normal = cross(corners_[1] - corners_[0], corners_[2] - corners_[0]);
    normal_ = Vector(normal.x, normal.y, normal.z).normalize();
}

float Plane::get_width() const {
    return width_;
}

float Plane::get_height() const {
    return height_;
}

const Vector& Plane::get_normal() const {
    return normal_;
}

const std::vector<glm::vec3>& Plane::get_corners() const {
    return corners_;
}

float Plane::checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const {
    return other->checkCollisionWithPlane(shared_from_this());
}

float Plane::checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const {
    return RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), plane);
}

float Plane::checkCollisionWithBox(const std::shared_ptr<const Box>& box) const {
    return RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), box);
}

const Sphere& Plane::get_bounding_sphere() const {
    return bounding_sphere_;
}
