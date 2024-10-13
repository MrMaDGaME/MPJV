#pragma once
#include "Particle.h"
#include "Vector.h"
#include "Force/IParticleForceGenerator.h"

class SpringForceGenerator : public IParticleForceGenerator {
private:
    Particle* other;
    float springConstant;
    float restLength;

public:
    SpringForceGenerator(Particle* other, float springConstant, float restLength);
    void UpdateForce(Particle* particle, float deltaTime) override;
};
