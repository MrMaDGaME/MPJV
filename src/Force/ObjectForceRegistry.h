#pragma once
#include "../Objects/Particle.h"
#include "IParticleForceGenerator.h"
#include "Generators/ImpulseForceGenerator.h"

class ObjectForceRegistry {
    struct ParticleForceRegistration {
        shared_ptr<IObject> object;
        shared_ptr<IParticleForceGenerator> force_generator;
    };

public:
    void add(const shared_ptr<IObject>& object, const shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(shared_ptr<IObject>& object, shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(shared_ptr<IObject>& object);
    void clear();
    void update_forces();

private:
    std::vector<ParticleForceRegistration> registrations_;
};
