#include "GravityForce.h"

void GravityForce::UpdateForce(Particle* particle, float deltaTime)
{
    if (particle == nullptr || particle->inv_mass == 0.0f)
    {
        return;
    }

    //particle->applyForce(gravity * particle->mass);
}
