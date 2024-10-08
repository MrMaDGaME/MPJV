#include "ParticleForceRegistry.h"

void ParticleForceRegistry::Add(Particle* particle, IParticleForceGenerator* forceGenerator)
{
    registrations.push_back({ particle, forceGenerator });
}

void ParticleForceRegistry::Remove(Particle* particle, IParticleForceGenerator* forceGenerator)
{
    registrations.erase(std::remove_if(registrations.begin(), registrations.end(), [particle, forceGenerator](const ParticleForceRegistration& registration)
    {
        return registration.particle == particle && registration.forceGenerator == forceGenerator;
    }), registrations.end());
}

void ParticleForceRegistry::Clear()
{
    registrations.clear();
}

void ParticleForceRegistry::UpdateForces(float duration)
{
    for(auto& registration : registrations)
    {
        registration.forceGenerator->UpdateForce(registration.particle, duration);
    }
}
