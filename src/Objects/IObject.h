#pragma once
#include "../maths/Vector.h"
#include "../Force/ObjectForceRegistry.h"

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
    [[nodiscard]] virtual shared_ptr<ObjectForceRegistry> get_global_force_registry() const = 0;
    virtual void set_global_force_registry(shared_ptr<ObjectForceRegistry> global_ptr) = 0;
};
