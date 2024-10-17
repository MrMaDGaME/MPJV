#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(const shared_ptr<Particle>& other, const float springConstant, const float restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {
}

void SpringForceGenerator::UpdateForce(shared_ptr<Particle>& particle) {
    Vector force = particle->position - other->position;
    float distance = force.magnitude();
    float magnitude = -springConstant * (distance - restLength);
    force = force.normalize();
    particle->addForce(Vector(force.x * magnitude, force.y * magnitude, force.z * magnitude));
}
