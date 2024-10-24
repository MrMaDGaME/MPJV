#pragma once
#include "../IParticleForceGenerator.h"

#define DEFAULT_GRAVITY 1.f //Define the default value of the gravity

#define DEFAULT_GRAVITY_DIRECTION Vector(0,1,0) //Unitary vector, define the direction of gravity

class GravityForceGenerator : public IParticleForceGenerator {
public:
    GravityForceGenerator(float gravity);
    GravityForceGenerator();
    void UpdateForce(std::shared_ptr<IObject>& object) override;

private:
    Vector _gravity;
};
