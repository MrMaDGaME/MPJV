#pragma once
#include "../Particle.h"
#include "IParticleForceGenerator.h"

class ParticleForceRegistry {
    struct ParticleForceRegistration {
        shared_ptr<Particle> particle;
        shared_ptr<IParticleForceGenerator> force_generator;
    };

public:
    void add(const shared_ptr<Particle>& particle, const shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(shared_ptr<Particle>& particle, shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(shared_ptr<Particle>& particle);
    void clear();
    void update_forces();

private:
    typedef std::vector<ParticleForceRegistration> registry;
    registry registrations_;
};
