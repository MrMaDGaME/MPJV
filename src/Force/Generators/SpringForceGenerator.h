#pragma once
#include "../IObjectForceGenerator.h"

class SpringForceGenerator : public IObjectForceGenerator {
public:
    SpringForceGenerator(const std::shared_ptr<IObject>& other, float springConstant, float restLength);
    void UpdateForce(std::shared_ptr<IObject>& object) override;
    void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) override;

private:
    std::shared_ptr<IObject> other;
    float springConstant;
    float restLength;
};
