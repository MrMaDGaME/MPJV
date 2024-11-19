#pragma once
#include "../IObjectForceGenerator.h"

class ImpulseForceGenerator : public IObjectForceGenerator {
public:
    ImpulseForceGenerator(const Vector& impulse);
    ImpulseForceGenerator(float x, float y, float z);
    void UpdateForce(std::shared_ptr<IObject>& object) override;
    void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) override;

private:
    Vector impulse_;
};
