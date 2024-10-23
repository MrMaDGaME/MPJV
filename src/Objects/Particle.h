#pragma once
#include "IObject.h"
#include "ofMain.h"

class Particle : public IObject, public std::enable_shared_from_this<Particle> {
public:
    Particle();
    Particle(float x, float y, float z);
    Particle(float x, float y, float z, float radius, float mass);
    Particle(float x, float y, float z, float radius, float mass, ofColor color, float terminal_velocity);
    Particle(float x, float y, float z, float radius, bool is_kinematic);

    void update() override;
    void draw() override;
    void addForce(const Vector& force) override;
    void clearAccum();
    [[nodiscard]] Vector get_position() const override;
    void set_position(const Vector& position) override;
    [[nodiscard]] Vector get_velocity() const override;
    void set_velocity(const Vector& velocity) override;
    [[nodiscard]] float get_inv_mass() const override;
    void set_inv_mass(float inv_mass) override;
    [[nodiscard]] float get_terminal_velocity() const;
    void set_terminal_velocity(float terminal_velocity);
    [[nodiscard]] float get_radius() const;
    void fill_object_collision(std::shared_ptr<IObject> other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    CollisionType collision_type, float coeff) override;//see IObject.h
    void fill_particle_collision(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    CollisionType collision_type, float coeff) override;//see IObject.h

protected:
    ofColor color_;

private:
    Vector position_;
    Vector velocity_;
    Vector accum_force_;
    float inv_mass_;
    float terminal_velocity_ = -1;
    float radius_;
};
