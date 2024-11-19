#include "RigidBody.h"

RigidBody::RigidBody(float x, float y, float z, float mass, Matrix3x3 inertia) {
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector(x, y, z);
    rotation_ = Quaternion();
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = 1 / mass;
    inv_inertia_ = inertia.inverse();
}

RigidBody::RigidBody(float x, float y, float z, float mass, Matrix3x3 inertia, ofColor color) {
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector(x, y, z);
    rotation_ = Quaternion();
    velocity_ = Vector(0, 0, 0);
    inv_mass_ = 1 / mass;
    inv_inertia_ = inertia.inverse();
    color_ = color;
}

void RigidBody::update() {
    float last_frame = static_cast<float>(ofGetLastFrameTime());
    Vector acceleration = accum_force_ * inv_mass_;
    position_ += (velocity_ * last_frame + acceleration * last_frame * last_frame / 2) * 100; //Passage en cm
    velocity_ += acceleration * last_frame;

    Vector angular_acceleration = inv_inertia_ * accum_torque;
    angular_velocity_ = inv_inertia_ * angular_acceleration;

    rotation_ = rotation_ + (rotation_ * Quaternion(0, angular_acceleration.x, angular_velocity_.y, angular_velocity_.z)) * (0.5f * last_frame);
    rotation_.normalize();

    inv_inertia_ = rotation_.ToMatrix3() * inv_inertia_ * rotation_.conjugate().ToMatrix3();
    clearAccums();
}

void RigidBody::addForce(const Vector& force) {
    accum_force_ += force;
}

void RigidBody::addForce(const Vector& force, const Vector& apply_point) {
    accum_force_ += force;
    Vector l = -position_ + apply_point;
    accum_torque += l ^ force;
}

void RigidBody::rotate(Quaternion rot_quat) {
    rotation_ = rot_quat * rotation_;
}

[[nodiscard]] Vector RigidBody::get_position() const {
    return position_;
}

void RigidBody::set_position(const Vector& position) {
    this->position_ = position;
}

[[nodiscard]] Vector RigidBody::get_velocity() const {
    return velocity_;
}

void RigidBody::set_velocity(const Vector& velocity) {
    this->velocity_ = velocity;
}

[[nodiscard]] float RigidBody::get_inv_mass() const {
    return inv_mass_;
}

void RigidBody::set_inv_mass(float inv_mass) {
    this->inv_mass_ = inv_mass;
}

void RigidBody::fill_object_collision(std::shared_ptr<IObject> other,
                                      std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                      CollisionType collision_type,
                                      float coeff) {
}

void RigidBody::fill_particle_collision(std::shared_ptr<Particle> particle,
                                        std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                        CollisionType collision_type,
                                        float coeff) {
}

void RigidBody::clearAccums() {
    accum_force_ = Vector(0, 0, 0);
    accum_torque = Vector(0, 0, 0);
}

void RigidBody::setCenterOfMass(const Vector& newCenterOfMass) {
    centerOfMass_ = newCenterOfMass;
}
