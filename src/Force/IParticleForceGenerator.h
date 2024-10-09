#pragma once
#include "Particle.h"

class IParticleForceGenerator
{
public:
    virtual void UpdateForce(Particle* particle, float deltaTime) = 0;
};
