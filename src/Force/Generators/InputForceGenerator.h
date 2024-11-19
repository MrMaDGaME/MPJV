#pragma once
#include "../IObjectForceGenerator.h"

class InputForceGenerator : public IObjectForceGenerator {
public:
    InputForceGenerator(const std::shared_ptr<Vector>& input, float force);
    void UpdateForce(std::shared_ptr<IObject>& object) override;
    void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) override;

private:
    std::shared_ptr<Vector> input_;
    float force_;
};
