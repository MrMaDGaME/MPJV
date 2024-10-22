#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gravity) {
    _gravity = DEFAULT_GRAVITY_DIRECTION *gravity;
}

GravityForceGenerator::GravityForceGenerator(){
     _gravity = DEFAULT_GRAVITY_DIRECTION*DEFAULT_GRAVITY;
    }

void GravityForceGenerator::UpdateForce(std::shared_ptr<IObject>& object) {
    if (object == nullptr || object->get_inv_mass() == 0.0f) {
        return;
    }
    object->addForce(_gravity / object->get_inv_mass());
}
