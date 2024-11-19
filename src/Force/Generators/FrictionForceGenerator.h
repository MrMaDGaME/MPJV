#pragma once
#include "../IObjectForceGenerator.h"

class FrictionForceGenerator : public IObjectForceGenerator {
public:
    FrictionForceGenerator(float friction);
    void UpdateForce(std::shared_ptr<IObject>& object) override;
    void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) override;

private:
    float friction_;
};
