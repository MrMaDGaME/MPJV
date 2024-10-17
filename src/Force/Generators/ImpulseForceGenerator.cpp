#include "ImpulseForceGenerator.h"

ImpulseForceGenerator::ImpulseForceGenerator(const Vector& impulse) : impulse_(impulse) {
}

ImpulseForceGenerator::ImpulseForceGenerator(const float x, const float y, const float z) : impulse_(x, y, z) {
}

void ImpulseForceGenerator::UpdateForce(shared_ptr<Particle>& particle) {
    if (particle == nullptr || particle->inv_mass == 0.0f) {
        return;
    }

    particle->addForce(impulse_ / particle->inv_mass);
}
