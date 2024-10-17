#pragma once
#include "../IParticleForceGenerator.h"

class ImpulseForceGenerator : public IParticleForceGenerator {
public:
    ImpulseForceGenerator(const Vector& impulse);
    ImpulseForceGenerator(float x, float y, float z);
    void UpdateForce(shared_ptr<Particle>& particle) override;

private:
    Vector impulse_;
};
