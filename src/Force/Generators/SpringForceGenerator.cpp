#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(const std::shared_ptr<IObject>& other, const float springConstant, const float restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {
}

void SpringForceGenerator::UpdateForce(std::shared_ptr<IObject>& object) {
    Vector force = object->get_position() - other->get_position();
    float distance = force.magnitude();
    float magnitude = -springConstant * (distance - restLength);
    force = force.normalize();
    object->addForce(Vector(force.x * magnitude, force.y * magnitude, force.z * magnitude));
}

void SpringForceGenerator::UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) {
    Vector force = object->get_position() - other->get_position();
    float distance = force.magnitude();
    float magnitude = -springConstant * (distance - restLength);
    force = force.normalize();
    object->addForce(Vector(force.x * magnitude, force.y * magnitude, force.z * magnitude), apply_point);
}
