#pragma once
#include "../Particle.h"
#include "IParticleForceGenerator.h"

class ParticleForceRegistry
{
private:
    struct ParticleForceRegistration
    {
        Particle* particle;
        shared_ptr<IParticleForceGenerator> force_generator;
    };
    typedef std::vector<ParticleForceRegistration> registry;

    registry registrations_;

public:
    void add(Particle* particle, shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(Particle* particle, shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(Particle* particle);
    void clear();
    void update_forces();
};
