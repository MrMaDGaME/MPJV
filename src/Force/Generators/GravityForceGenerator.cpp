#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(float gravity) {
    _gravity = Vector(0.f, gravity, 0.f);
}

void GravityForceGenerator::UpdateForce(shared_ptr<Particle>& particle) {
    if (particle == nullptr || particle->inv_mass == 0.0f) {
        return;
    }

    particle->addForce(_gravity / particle->inv_mass);
}
