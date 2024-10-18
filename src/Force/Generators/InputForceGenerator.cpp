#include "InputForceGenerator.h"

InputForceGenerator::InputForceGenerator(const shared_ptr<Vector>& input, const float force) : input_(input), force_(force) {
}

void InputForceGenerator::UpdateForce(shared_ptr<IObject>& object) {
    object->addForce(input_->normalize() * force_);
}
