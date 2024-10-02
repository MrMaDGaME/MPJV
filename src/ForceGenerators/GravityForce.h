#pragma once
#include "ParticleForceGenerator.h"

class GravityForce : ParticleForceGenerator
{
private:
    Vector gravity;
    
public:
    void UpdateForce(Particle* particle, float deltaTime) override;
};
