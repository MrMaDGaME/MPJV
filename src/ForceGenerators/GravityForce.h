#pragma once
#include "ParticleForceGenerator.h"

class GravityForce : ParticleForceGenerator
{
public:
    void UpdateForce(Particle* particle, float deltaTime) const override;
};
