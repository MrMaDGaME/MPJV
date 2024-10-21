#pragma once
#include "../IParticleForceGenerator.h"

class InputForceGenerator : public IParticleForceGenerator {
public:
    InputForceGenerator(const std::shared_ptr<Vector>& input, float force);
    void UpdateForce(std::shared_ptr<IObject>& object) override;

private:
    std::shared_ptr<Vector> input_;
    float force_;
};
