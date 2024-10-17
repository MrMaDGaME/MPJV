#pragma once
#include "../../Particle.h"
#include "../../Vector.h"
#include "../IParticleForceGenerator.h"

class SpringForceGenerator : public IParticleForceGenerator {
public:
    SpringForceGenerator(const shared_ptr<Particle>& other, float springConstant, float restLength);
    void UpdateForce(shared_ptr<Particle>& particle) override;

private:
    shared_ptr<Particle> other;
    float springConstant;
    float restLength;
};
