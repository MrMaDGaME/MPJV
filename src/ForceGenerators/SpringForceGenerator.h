#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
#include "Vector.h"

class SpringForceGenerator : public ForceGenerator {
private:
    Particle* other;
    float springConstant;
    float restLength;

public:
    SpringForceGenerator(Particle* other, float springConstant, float restLength);
    void applyForce(Particle& particle) override;
};
