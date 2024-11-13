#include "Box.h"

Box::Box(float x, float y, float z, float height, float width, float depth, float mass,float inertia) : RigidBody(x, y, z, mass, inertia), height_(height), width_(width), depth_(depth) {
}
    
Box::Box(float x, float y, float z, float height, float width, float depth, float mass, float inertia, ofColor color) : RigidBody(x, y, z, mass, inertia, color), height_(height), width_(width), depth_(depth) {
}

void Box::draw() {
    ofSetColor(color_);
    ofDrawRectangle(position_.x, position_.y, position_.z, width_, height_);
}
