#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gravity) {
    _gravity = Vector(0.f, gravity, 0.f);
}

void GravityForceGenerator::UpdateForce(shared_ptr<IObject>& object) {
    if (object == nullptr || object->get_inv_mass() == 0.0f) {
        return;
    }
    object->addForce(_gravity / object->get_inv_mass());
}
