#pragma once
#include "../IParticleForceGenerator.h"

class InputForceGenerator : public IParticleForceGenerator {
public:
    InputForceGenerator(const shared_ptr<Vector>& input, float force);
    void UpdateForce(shared_ptr<IObject>& object) override;

private:
    shared_ptr<Vector> input_;
    float force_;
};
