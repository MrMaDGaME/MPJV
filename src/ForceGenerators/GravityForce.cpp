#include "GravityForce.h"

void GravityForce::UpdateForce(Particle* particle, float deltaTime)
{
    if (particle == nullptr || particle->inv_mass == 0.0f)
    {
        return;
    }

    particle->addForce(gravity * particle->inv_mass);
}
