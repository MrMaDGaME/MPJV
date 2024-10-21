#pragma once
#include "../IParticleForceGenerator.h"

class SpringForceGenerator : public IParticleForceGenerator {
public:
    SpringForceGenerator(const std::shared_ptr<IObject>& other, float springConstant, float restLength);
    void UpdateForce(std::shared_ptr<IObject>& object) override;

private:
    std::shared_ptr<IObject> other;
    float springConstant;
    float restLength;
};
