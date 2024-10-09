#pragma once
#include "IParticleForceGenerator.h"

class GravityForceGenerator : public IParticleForceGenerator
{
private:
    Vector _gravity;
    
public:
    GravityForceGenerator(float gravity);
    
    void UpdateForce(Particle* particle, float deltaTime) override;
};
