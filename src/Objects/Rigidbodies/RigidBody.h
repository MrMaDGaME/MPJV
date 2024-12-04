#pragma once

#define _USE_MATH_DEFINES
#include "../IObject.h"
#include "ofMain.h"
#include "../../maths/Matrix3x3.h"
#include "../../maths/Matrix4x4.h"
#include "../../maths/Quaternion.h"
#include "../../maths/geometry/Sphere.h"

class RigidBody : public IObject, public std::enable_shared_from_this<RigidBody> {
protected:
    RigidBody(float x, float y, float z, float mass, Matrix3x3 inertia);
    RigidBody(float x, float y, float z, float mass, Matrix3x3 inertia, ofColor color);
    RigidBody(const Vector& position, float mass, Matrix3x3 inertia);
    RigidBody(const Vector& position, float mass, Matrix3x3 inertia, ofColor color);
    RigidBody(float x, float y, float z);
    RigidBody(float x, float y, float z, const ofColor& color);
    RigidBody(const Vector& position);
    RigidBody(const Vector& position, const ofColor& color);

public:
    void update() override;
    void addForce(const Vector& force) override;
    void addForce(const Vector& force, const Vector& apply_point) override;

    virtual void rotate(const Quaternion& rot_quat);

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
    void setCenterOfMass(const Vector& newCenterOfMass);

    static std::tuple<float, float, float> quaternionToEuler(float w, float x, float y, float z);

    Sphere getBoundingSphere() const;

private :
    void clearAccums();

protected:
    Vector position_;
    Quaternion rotation_;
    Vector velocity_;
    Vector angular_velocity_;
    Vector accum_force_;
    Vector accum_torque;
    float inv_mass_;
    Matrix3x3 inv_inertia_;
    ofColor color_;
    Vector centerOfMass_; // Variable pour stocker le centre de masse
    Sphere boundingSphere_;
};
