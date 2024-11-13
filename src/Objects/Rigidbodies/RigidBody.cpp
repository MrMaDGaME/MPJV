#include "RigidBody.h"

RigidBody::RigidBody(float x, float y, float z, float mass,Matrix3x3 inertia){
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector (x,y,z);
    velocity_ = Vector(0,0,0);
    inv_mass_ = 1/mass;
    inv_inertia_ = inertia.inverse(); 
}
    
RigidBody::RigidBody(float x, float y, float z, float mass, Matrix3x3 inertia, ofColor color){
        if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector (x,y,z);
    velocity_ = Vector(0,0,0);
    inv_mass_ = 1/mass;
    inv_inertia_ = inertia.inverse(); 
}

//    void update() ;

void RigidBody::addForce(const Vector& force) {
        accum_force_ += force;
}
void RigidBody::addForce(const Vector& applyPoint, const Vector& force){
        accum_force_ += force;
        Vector l =  -  position_  + applyPoint;
        accum_torque +=  l^force;
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
void fill_object_collision(std::shared_ptr<IObject> other,
                                       std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                       CollisionType collision_type,
                                       float coeff) {}
void fill_particle_collision(std::shared_ptr<Particle> particle,
                                         std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                         CollisionType collision_type,
                                         float coeff){}
