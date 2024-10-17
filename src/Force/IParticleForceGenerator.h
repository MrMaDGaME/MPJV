#pragma once
#include "../Particle.h"

class IParticleForceGenerator {
public:
    virtual ~IParticleForceGenerator() = default;
    virtual void UpdateForce(shared_ptr<Particle>& particle) = 0;
};
