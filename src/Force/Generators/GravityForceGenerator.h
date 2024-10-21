#pragma once
#include "../IParticleForceGenerator.h"

class GravityForceGenerator : public IParticleForceGenerator {
public:
    GravityForceGenerator(float gravity);
    void UpdateForce(std::shared_ptr<IObject>& object) override;

private:
    Vector _gravity;
};
