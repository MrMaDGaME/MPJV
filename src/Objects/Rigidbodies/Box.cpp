#include "Box.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia) : RigidBody(x, y, z, mass, inertia),
    height_(height),
    width_(width),
    depth_(depth) {
}

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color) :
    RigidBody(x, y, z, mass, inertia, color),
    height_(height),
    width_(width),
    depth_(depth) {
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
