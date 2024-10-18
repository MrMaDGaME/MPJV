#pragma once
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
