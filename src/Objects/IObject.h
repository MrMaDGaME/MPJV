#pragma once
#include <memory>
#include "../maths/Vector.h"

class Particle;
class ParticleCollisionRegistry;


class IObject {
public:
    virtual ~IObject() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void addForce(const Vector& force) = 0;

    [[nodiscard]] virtual Vector get_position() const = 0;
    virtual void set_position(const Vector& position) = 0;
    [[nodiscard]] virtual Vector get_velocity() const = 0;
    virtual void set_velocity(const Vector& velocity) = 0;
    [[nodiscard]] virtual float get_inv_mass() const = 0;
    virtual void set_inv_mass(float inv_mass) = 0;
    virtual void checkObjectCollision(std::shared_ptr<IObject>& other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry) = 0;
    virtual void checkParticleCollision(std::shared_ptr<Particle>& particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry) = 0;
};
