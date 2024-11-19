#pragma once
#include "../IObjectForceGenerator.h"

#define DEFAULT_GRAVITY 1.f //Define the default value of the gravity

#define DEFAULT_GRAVITY_DIRECTION Vector(0,1,0) //Unitary vector, define the direction of gravity

class GravityForceGenerator : public IObjectForceGenerator {
public:
    GravityForceGenerator(float gravity);
    GravityForceGenerator();
    void UpdateForce(std::shared_ptr<IObject>& object) override;
    void UpdateForce(std::shared_ptr<IObject>& object, const Vector& apply_point) override;
    void setGravity(float gravity);

private:
    Vector _gravity;
};
