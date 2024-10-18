#pragma once
#include "../Objects/Particle.h"

class IParticleForceGenerator {
public:
    virtual ~IParticleForceGenerator() = default;
    virtual void UpdateForce(shared_ptr<IObject>& object) = 0;
};
