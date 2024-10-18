#include "FrictionForceGenerator.h"

FrictionForceGenerator::FrictionForceGenerator(float friction) : friction_(friction) {}

void FrictionForceGenerator::UpdateForce(shared_ptr<Particle>& particle) {
    Vector force = particle->velocity;
    force.normalize();
    force *= -friction_;
    particle->addForce(force);
}
