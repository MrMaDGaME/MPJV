#include "ImpulseForceGenerator.h"

ImpulseForceGenerator::ImpulseForceGenerator(const Vector& impulse) : impulse_(impulse) {
}

ImpulseForceGenerator::ImpulseForceGenerator(const float x, const float y, const float z) : impulse_(x, y, z) {
}

void ImpulseForceGenerator::UpdateForce(std::shared_ptr<IObject>& object) {
    if (object == nullptr) {
        return;
    }
    object->addForce(impulse_);
}

void ImpulseForceGenerator::UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) {
    if (object == nullptr) {
        return;
    }
    object->addForce(impulse_, apply_point);
}
