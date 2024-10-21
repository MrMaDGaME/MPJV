#pragma once
#include "../Objects/Particle.h"
#include "IParticleForceGenerator.h"
#include "Generators/ImpulseForceGenerator.h"

class ObjectForceRegistry {
    struct ParticleForceRegistration {
        std::shared_ptr<IObject> object;
        std::shared_ptr<IParticleForceGenerator> force_generator;
    };

public:
    void add(const std::shared_ptr<IObject>& object, const std::shared_ptr<IParticleForceGenerator>& force_generator);
    bool remove(std::shared_ptr<IObject>& object, std::shared_ptr<IParticleForceGenerator>& force_generator);
    void remove(std::shared_ptr<IObject>& object);
    void clear();
    void update_forces();

private:
    std::vector<ParticleForceRegistration> registrations_;
};
