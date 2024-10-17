#pragma once
#include "../IParticleForceGenerator.h"

class GravityForceGenerator : public IParticleForceGenerator {
private:
    Vector _gravity;

public:
    GravityForceGenerator(float gravity);

    void UpdateForce(shared_ptr<Particle>& particle) override;
};
