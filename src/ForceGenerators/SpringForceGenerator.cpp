#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Particle* other, float springConstant, float restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {}

void SpringForceGenerator::applyForce(Particle& particle) {
    Vector force = particle.position - other->position;
    float distance = force.magnitude();
    float magnitude = -springConstant * (distance - restLength);
    force = force.normalize();
    particle.applyForce(force.x * magnitude, force.y * magnitude, force.z * magnitude, 0.f);
}
