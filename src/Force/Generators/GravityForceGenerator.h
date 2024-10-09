#pragma once
#include "IParticleForceGenerator.h"

class GravityForce : public IParticleForceGenerator
{
private:
    Vector gravity;
    
public:
    void UpdateForce(Particle* particle, float deltaTime) override;
};
