#include "Box.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia) : RigidBody(x, y, z, mass, inertia),
    width_(width), height_(height), depth_(depth) {
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height + depth * depth) / 2);
}

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color) :
    RigidBody(x, y, z, mass, inertia, color), width_(width), height_(height), depth_(depth) {
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height + depth * depth) / 2);
}

void Box::draw() {
    ofSetColor(color_);

    auto [roll, pitch, yaw] = quaternionToEuler(rotation_.w, rotation_.x, rotation_.y, rotation_.z);

    // Appliquer les rotations et dessiner la boîte
    ofPushMatrix();
    ofTranslate(glm::vec3(position_.x, position_.y, position_.z)); // Position globale
    ofRotateXDeg(roll); // Rotation autour de X (Roll)
    ofRotateYDeg(pitch); // Rotation autour de Y (Pitch)
    ofRotateZDeg(yaw); // Rotation autour de Z (Yaw)
    ofDrawBox(0, 0, 0, width_, height_, depth_); // Dessine une boîte centrée à l'origine avec la taille donnée
    ofPopMatrix();
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

float Box::checkCollisionWithRigidbody(const std::shared_ptr<const RigidBody>& other) const {
    return other->checkCollisionWithBox(shared_from_this());
}

float Box::checkCollisionWithPlane(const std::shared_ptr<const Plane>& plane) const {
    return RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), plane);
}

float Box::checkCollisionWithBox(const std::shared_ptr<const Box>& box) const {
    return RigidbodyCollisionRegistry::checkInterCollision(shared_from_this(), box);
}
