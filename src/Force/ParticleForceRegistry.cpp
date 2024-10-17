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

void ParticleForceRegistry::Remove(Particle* particle)
{
    registrations.erase(std::remove_if(registrations.begin(), registrations.end(), [particle](const ParticleForceRegistration& registration)
    {
        return registration.particle == particle;
    }), registrations.end());
}

void ParticleForceRegistry::Clear()
{
    registrations.clear();
}

void ParticleForceRegistry::UpdateForces()
{
    for(auto& registration : registrations)
    {
        registration.forceGenerator->UpdateForce(registration.particle);
    }
}
