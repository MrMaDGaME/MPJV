#pragma once
#include "../IParticleForceGenerator.h"

class SpringForceGenerator : public IParticleForceGenerator {
public:
    SpringForceGenerator(const shared_ptr<IObject>& other, float springConstant, float restLength);
    void UpdateForce(shared_ptr<IObject>& object) override;

private:
    shared_ptr<IObject> other;
    float springConstant;
    float restLength;
};
