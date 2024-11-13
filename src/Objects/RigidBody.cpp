#include "RigidBody.h"

RigidBody::RigidBody(float x, float y, float z, float mass,float inertia){
    if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector (x,y,z);
    velocity_ = Vector(0,0,0);
    inv_mass_ = 1/mass;
    inertia_ = inertia; 
}
    
RigidBody::RigidBody(float x, float y, float z, float mass, float intertia, ofColor color){
        if (mass <= 0.f) {
        throw std::invalid_argument("Mass must be positive");
    }
    position_ = Vector (x,y,z);
    velocity_ = Vector(0,0,0);
    inv_mass_ = 1/mass;
    inertia_ = inertia; 
}

//    void update() override;

void RigidBody::draw() {
    ofSetColor(color_);
    ofDrawRectangle(position_.x, position_.y, position_.z, width_, height_);
}
void RigidBody::addForce(const Vector& force) override{
        accum_force_ += force;
}
    void addForce(const Vector& applyPoint, const Vector& force){
        accum_force_ += force;
    }


    [[nodiscard]] Vector get_position() const override;
    void set_position(const Vector& position) override;
    [[nodiscard]] Vector get_velocity() const override;
    void set_velocity(const Vector& velocity) override;
    [[nodiscard]] float get_inv_mass() const override;
    void set_inv_mass(float inv_mass) override;
    virtual void fill_object_collision(std::shared_ptr<IObject> other,
                                       std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                       CollisionType collision_type,
                                       float coeff) override;
    void fill_particle_collision(std::shared_ptr<Particle> particle,
                                         std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                         CollisionType collision_type,
                                         float coeff) override;
