#pragma once
#include "../IParticleForceGenerator.h"

class FrictionForceGenerator : public IParticleForceGenerator {
public:
    FrictionForceGenerator(float friction);
    void UpdateForce(shared_ptr<Particle>& particle) override;

private:
    float friction_;
};
