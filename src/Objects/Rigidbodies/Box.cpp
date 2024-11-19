#include "Box.h"

#include "../../maths/Matrix4x4.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia) : RigidBody(x, y, z, mass, inertia), height_(height), width_(width), depth_(depth) {
}
    
Box::Box(float x, float y, float z, float height, float width, float depth, float mass, Matrix3x3 inertia, ofColor color) : RigidBody(x, y, z, mass, inertia, color), height_(height), width_(width), depth_(depth) {
}

void Box::draw() {
    ofSetColor(color_);
    // Appliquer transformations avec quaternion et position
    ofPushMatrix();
    ofTranslate(glm::vec3(position_.x, position_.y, position_.z)); // Position globale

    // Appliquer la rotation du quaternion
    ofMatrix4x4 rotationMatrix = rotation_.ToMatrix4().ToOfMatrix(); // Convertir en matrice 4x4
    ofMultMatrix(rotationMatrix);                        // Appliquer la matrice

    ofSetColor(100, 200, 255);   // Couleur de la boîte
    ofDrawBox(0, 0, 0, width_, height_, depth_); // Dessine une boîte centrée à (0, 0, 0) dans le repère local
    ofPopMatrix();

}
