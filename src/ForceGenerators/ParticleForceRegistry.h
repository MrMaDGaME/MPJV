#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
    struct ParticleForceRegistration
    {
        Particle* particle;
        ParticleForceGenerator* forceGenerator;
    };
    typedef std::vector<ParticleForceRegistration> registry;

    registry registrations;

public:
    void Add(Particle* particle, ParticleForceGenerator* forceGenerator);
    void Remove(Particle* particle, ParticleForceGenerator* forceGenerator);
    void Clear();
    void UpdateForces(float duration);
};
