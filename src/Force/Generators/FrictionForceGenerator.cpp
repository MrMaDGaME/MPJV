#include "FrictionForceGenerator.h"

FrictionForceGenerator::FrictionForceGenerator(float friction) : friction_(friction) {
}

void FrictionForceGenerator::UpdateForce(std::shared_ptr<IObject>& object) {
    Vector force = object->get_velocity();
    force.normalize();
    force *= -friction_;
    object->addForce(force);
}
