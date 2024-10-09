#pragma once
#include "Particle.h"
#include "IParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
    struct ParticleForceRegistration
    {
        Particle* particle;
        IParticleForceGenerator* forceGenerator;
    };
    typedef std::vector<ParticleForceRegistration> registry;

    registry registrations;

public:
    void Add(Particle* particle, IParticleForceGenerator* forceGenerator);
    void Remove(Particle* particle, IParticleForceGenerator* forceGenerator);
    void Clear();
    void UpdateForces(float duration);
};
