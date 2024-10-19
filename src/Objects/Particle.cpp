#include "Particle.h"

Particle::Particle() {
    position_ = Vector(0, 0, 0);
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = 1;
    radius_ = 10;
}

Particle::Particle(const float x, const float y, const float z) {
    position_ = Vector(x, y, z);
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = 1;
    radius_ = 10;
}

Particle::Particle(const float x, const float y, const float z, const float radius, const float mass) {
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector(x, y, z);
    velocity_ = Vector(0, 0, 0);
    this->inv_mass_ = 1 / mass;
    this->radius_ = radius;
}

Particle::Particle(float x, float y, float z, float radius, float mass, ofColor color, float terminal_velocity) {
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector(x, y, z);
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = 1 / mass;
    this->radius_ = radius;
    this->color_ = color;
    set_terminal_velocity(terminal_velocity);
}

Particle::Particle(float x, float y, float z, float radius, bool is_kinematic = false) {
    position_ = Vector(x, y, z);
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = is_kinematic ? 0 : 1;
    this->radius_ = radius;
}

void Particle::update() {
    float last_frame = static_cast<float>(ofGetLastFrameTime());
    Vector acceleration = accum_force_ * inv_mass_;
    // /!\ Orde de calcul important !!! La position doit être calculée avant la vitesse
    position_ += (velocity_ * last_frame + acceleration * last_frame * last_frame / 2) * 100; // Passage en cm
    velocity_ += acceleration * last_frame;
    if (terminal_velocity_ > 0 && velocity_.magnitude() > terminal_velocity_) {
        velocity_ = velocity_.normalize() * terminal_velocity_;
    }
    clearAccum();
}

void Particle::draw() {
    ofSetColor(color_);
    ofDrawSphere(position_.x, position_.y, position_.z, radius_);
}

void Particle::addForce(const Vector& force) {
    accum_force_ += force;
}

void Particle::clearAccum() {
    accum_force_ = Vector(0, 0, 0);
}

Vector Particle::get_position() const {
    return position_;
}

void Particle::set_position(const Vector& position) {
    this->position_ = position;
}

Vector Particle::get_velocity() const {
    return velocity_;
}

void Particle::set_velocity(const Vector& velocity) {
    this->velocity_ = velocity;
}

float Particle::get_inv_mass() const {
    return inv_mass_;
}

void Particle::set_global_force_registry(shared_ptr<ObjectForceRegistry> global_ptr){
    global_force_registry.swap(global_ptr);
}

shared_ptr<ObjectForceRegistry> Particle::get_global_force_registry(){
    return global_force_registry;
}

void Particle::set_inv_mass(float inv_mass) {
    this->inv_mass_ = inv_mass;
}

float Particle::get_terminal_velocity() const {
    return terminal_velocity_;
}

void Particle::set_terminal_velocity(float terminal_velocity) {
    if (terminal_velocity < 0) {
        throw std::invalid_argument("Terminal velocity must be positive");
    }
    this->terminal_velocity_ = terminal_velocity;
}

float Particle::get_radius() const {
    return radius_;
}
