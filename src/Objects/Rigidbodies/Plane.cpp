#include "Plane.h"

Plane::Plane(const float x, const float y, const float z, const float width, const float height, const Vector& normal) : RigidBody(x, y, z),
    width_(width),
    height_(height),
    normal_(normal) {
    rotation_ = normalToQuat(normal);
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height) / 2);
}

Plane::Plane(const float x, const float y, const float z, const float width, const float height, const Vector& normal, const ofColor& color) :
    RigidBody(x, y, z, color),
    width_(width),
    height_(height),
    normal_(normal) {
    rotation_ = normalToQuat(normal);
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height) / 2);
}

Plane::Plane(const Vector& position, const float width, const float height, const Vector& normal) : RigidBody(position),
    width_(width),
    height_(height),
    normal_(normal) {
    rotation_ = normalToQuat(normal);
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height) / 2);
}

Plane::Plane(const Vector& position, const float width, const float height, const Vector& normal, const ofColor& color) : RigidBody(position, color),
    width_(width),
    height_(height),
    normal_(normal) {
    rotation_ = normalToQuat(normal);
    boundingSphere_ = Sphere(position_, std::sqrt(width * width + height * height) / 2);
}

void Plane::draw() {
    ofSetColor(color_);

    auto [roll, pitch, yaw] = quaternionToEuler(rotation_.w, rotation_.x, rotation_.y, rotation_.z);

    // Appliquer les rotations et dessiner la boîte
    ofPushMatrix();
    ofTranslate(glm::vec3(position_.x, position_.y, position_.z)); // Position globale
    ofRotateXDeg(roll); // Rotation autour de X (Roll)
    ofRotateYDeg(pitch); // Rotation autour de Y (Pitch)
    ofRotateZDeg(yaw); // Rotation autour de Z (Yaw)
    ofDrawPlane(position_.x, position_.y, position_.z, width_, height_);
    ofPopMatrix();
    ofSetColor(ofColor::red);
    // ofDrawArrow(glm::vec3(position_.x, position_.y, position_.z),
    //             glm::vec3(position_.x, position_.y, position_.z) + glm::vec3(normal_.x, normal_.y, normal_.z) * 50.f,
    //             5.f);
}

void Plane::update() {
    RigidBody::update();
    normal_ = quatToNormal(rotation_);
}

void Plane::rotate(const Quaternion& rot_quat) {
    RigidBody::rotate(rot_quat);
    normal_ = quatToNormal(rotation_);
}

Quaternion Plane::normalToQuat(const Vector& normal) {
    Vector identity = {0.0f, 0.0f, 1.0f}; // Normale identitaire

    Vector axis = identity.cross(normal); // Axe de rotation

    axis = axis.normalize();
    float angle = std::acos(identity.dot(normal) / (identity.magnitude() * normal.magnitude()));

    float halfAngle = angle / 2.0f;
    float sinHalfAngle = std::sin(halfAngle);

    return {std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle};
}

Vector Plane::quatToNormal(const Quaternion& quat) {
    // Quaternion représentant le vecteur identitaire (0, 0, 1)
    Quaternion v = {0.0f, 0.0f, 0.0f, 1.0f};

    // Appliquer la rotation : quat * v * quat^-1
    Quaternion qConjugate = quat.conjugate();
    Quaternion rotated = quat * v * qConjugate;

    // Extraire le vecteur résultant
    return {rotated.x, rotated.y, rotated.z};
}
