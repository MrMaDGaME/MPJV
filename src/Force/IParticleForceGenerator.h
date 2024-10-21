#pragma once
#include "../Objects/IObject.h"

class IParticleForceGenerator {
public:
    virtual ~IParticleForceGenerator() = default;
    virtual void UpdateForce(std::shared_ptr<IObject>& object) = 0;
};
