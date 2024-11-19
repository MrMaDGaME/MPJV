#include "InputForceGenerator.h"

InputForceGenerator::InputForceGenerator(const std::shared_ptr<Vector>& input, const float force) : input_(input), force_(force) {
}

void InputForceGenerator::UpdateForce(std::shared_ptr<IObject>& object) {
    object->addForce(input_->normalize() * force_);
}

void InputForceGenerator::UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) {
    object->addForce(input_->normalize() * force_, apply_point);
}
