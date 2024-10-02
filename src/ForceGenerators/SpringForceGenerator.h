#pragma once
#include "ForceGenerator.h"
#include "Vector.h"

class SpringForceGenerator : public ForceGenerator {
private:
    Particle* other; 
    float springConstant;
    float restLength;  

public:
    // Constructeur
    SpringForceGenerator(Particle* other, float springConstant, float restLength)
        : other(other), springConstant(springConstant), restLength(restLength) {}

    // Appliquer la force de ressort 
    void applyForce(Particle& particle) override {
        Vector force = particle.position - other->position;

        float distance = force.magnitude();
        float magnitude = -springConstant * (distance - restLength);

        force = force.normalize();

        particle.applyForce(force.x * magnitude, force.y * magnitude, force.z * magnitude, 0.f);
    }
};
