#pragma once
#include "IObject.h"
#include "ofMain.h"
#include "../maths/Matrix3x3.h"

class RigidBody : public IObject, public std::enable_shared_from_this<RigidBody> {

protected:
    RigidBody(float x, float y, float z, float mass,float inertia);
    RigidBody(float x, float y, float z, float mass, float intertia, ofColor color);
public:
    void update() override;
    void draw() override;
    void addForce(const Vector& force) override;
    void addForce(const Vector& applyPoint, const Vector& force);


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

protected:
    Vector position_;
    Vector velocity_;
    Vector accum_force_;
    float inv_mass_;
    Matrix3x3 inv_inertia_;
    ofColor color_;


};
