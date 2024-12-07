#pragma once
#include "../Objects/IObject.h"

class IObjectForceGenerator {
public:
    virtual ~IObjectForceGenerator() = default;
    virtual void UpdateForce(std::shared_ptr<IObject>& object) = 0;
    virtual void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) = 0;
};
