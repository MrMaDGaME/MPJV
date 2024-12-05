#pragma once
#include <memory>

#include "../maths/Vector.h"
#include "../Collision/CollisionType.h"

class ParticleCollisionRegistry;
class Particle;

class IObject {
public:
    virtual ~IObject() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void addForce(const Vector& force) = 0;
    virtual void addForce(const Vector& force, const Vector& apply_point) = 0;

    [[nodiscard]] virtual Vector get_position() const = 0;
    virtual void set_position(const Vector& position) = 0;
    [[nodiscard]] virtual Vector get_velocity() const = 0;
    virtual void set_velocity(const Vector& velocity) = 0;
    [[nodiscard]] virtual float get_inv_mass() const = 0;
    virtual void set_inv_mass(float inv_mass) = 0;
    virtual void fill_object_collision(std::shared_ptr<IObject> other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                       CollisionType collision_type, float coeff) = 0;
    //Called to initialise collision listener with another IObject without knowing it's nature : other object, collision_registry : the collision_registry to register it, collision_type : element of an enum, coeff is the value defining bounce on interpenetration and length on rod and cable
    virtual void fill_particle_collision(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
                                         CollisionType collision_type, float coeff) = 0;
    //Called to initialise collision listener with a Particle without knowing it's nature : other object, collision_registry : the collision_registry to register it, collision_type : element of an enum, coeff is the value defining bounce on interpenetration and length on rod and cable
};
