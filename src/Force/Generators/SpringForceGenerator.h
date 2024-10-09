#pragma once
#include "IParticleForceGenerator.h"
#include "Particle.h"
#include "Vector.h"

class SpringForceGenerator : public IParticleForceGenerator {
private:
    Particle* other;
    float springConstant;
    float restLength;

public:
    SpringForceGenerator(Particle* other, float springConstant, float restLength);
    void UpdateForce(Particle* particle, float deltaTime) override;
};
