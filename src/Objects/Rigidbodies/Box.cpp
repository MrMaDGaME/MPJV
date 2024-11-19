#include "Box.h"

#include "../../maths/Matrix4x4.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia) : RigidBody(x, y, z, mass, inertia), height_(height), width_(width), depth_(depth) {
}
    
Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color) : RigidBody(x, y, z, mass, inertia, color), height_(height), width_(width), depth_(depth) {
}

std::tuple<float, float, float> quaternionToEuler(float w, float x, float y, float z) {
    // Calcul du roll (rotation autour de X)
    float roll = std::atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y));

    // Calcul du pitch (rotation autour de Y)
    float sinPitch = 2.0f * (w * y - z * x);
    float pitch;
    if (std::abs(sinPitch) >= 1.0f) {
        pitch = std::copysign(M_PI / 2.0f, sinPitch); // Limiter à ±90°
    } else {
        pitch = std::asin(sinPitch);
    }

    // Calcul du yaw (rotation autour de Z)
    float yaw = std::atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z));

    // Convertir en degrés
    return std::make_tuple(ofRadToDeg(roll), ofRadToDeg(pitch), ofRadToDeg(yaw));
}

void Box::draw() {
    ofSetColor(color_);

    auto [roll, pitch, yaw] = quaternionToEuler(rotation_.w, rotation_.x, rotation_.y, rotation_.z);

    // Appliquer les rotations et dessiner la boîte
    ofPushMatrix();
    ofTranslate(glm::vec3(position_.x, position_.y, position_.z)); // Position globale
    ofRotateXDeg(roll);  // Rotation autour de X (Roll)
    ofRotateYDeg(pitch); // Rotation autour de Y (Pitch)
    ofRotateZDeg(yaw);   // Rotation autour de Z (Yaw)
    ofDrawBox(0, 0, 0, width_, height_, depth_); // Dessine une boîte centrée à l'origine avec la taille donnée
    ofPopMatrix();

}
