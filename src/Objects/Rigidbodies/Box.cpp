#include "Box.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia) : RigidBody(x, y, z, mass, inertia),
    width_(width), height_(height), depth_(depth), bounding_sphere_(position_, std::sqrt((width * width + height * height + depth * depth) / 4)) {
}

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color) :
    RigidBody(x, y, z, mass, inertia, color), width_(width), height_(height), depth_(depth),
    bounding_sphere_(position_, std::sqrt((width * width + height * height + depth * depth) / 4)) {
}

void Box::draw() {
    ofSetColor(color_);
    ofPushMatrix();
    for (size_t i = 0; i < 4; ++i) {
        // Relier les coins avant/arrière
        ofDrawLine(corners_[i], corners_[(i + 1) % 4]); // Face avant
        ofDrawLine(corners_[i + 4], corners_[(i + 1) % 4 + 4]); // Face arrière
        ofDrawLine(corners_[i], corners_[i + 4]); // Relier avant-arrière
    }
    ofPopMatrix();
}

void Box::set_bounding_sphere_position() {
    bounding_sphere_.set_center(position_);
}

void Box::set_corners() {
    int p = 0;
    for (float i = -0.5; i <= 0.5; i += 1) {
        for (float j = -0.5; j <= 0.5; j += 1) {
            for (float k = -0.5; k <= 0.5; k += 1) {
                // TODO : compute corner location with quaternion
                const auto corner = Vector(i * width_, j * height_, k * depth_);
                const auto rotated = rotation_ * Quaternion(0, corner.x, corner.y, corner.z) * rotation_.conjugate();
                corners_[p] = glm::vec3(rotated.x + position_.x, rotated.y + position_.y, rotated.z + position_.z);
                p++;
            }
        }
    }
    // swap the corners to match the correct order
    auto tmp = corners_[2];
    corners_[2] = corners_[3];
    corners_[3] = tmp;
    tmp = corners_[6];
    corners_[6] = corners_[7];
    corners_[7] = tmp;
}

float Box::get_width() const {
    return width_;
}

float Box::get_height() const {
    return height_;
}

float Box::get_depth() const {
    return depth_;
}

const std::vector<glm::vec3>& Box::get_corners() const {
    return corners_;
}

float Box::checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const {
    return other->checkCollisionWithBox(shared_from_this());
}

float Box::checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const {
    return RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), plane);
}

float Box::checkCollisionWithBox(const std::shared_ptr<const Box>& box) const {
    const auto result = RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), box);
    if (!RigidbodyCollisionRegistry::get_apply_points().empty()) {
        return result;
    }
    return RigidbodyCollisionRegistry::checkInterCollision(box, shared_from_this());
}

const Sphere& Box::get_bounding_sphere() const {
    return bounding_sphere_;
}
