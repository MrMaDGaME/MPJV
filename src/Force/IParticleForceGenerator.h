#pragma once
#include "../Particle.h"

class IParticleForceGenerator
{
public:
    virtual ~IParticleForceGenerator() = default;
    virtual void UpdateForce(Particle* particle) = 0;
};
