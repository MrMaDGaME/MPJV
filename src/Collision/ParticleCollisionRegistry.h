#pragma once

#include "../Force/ObjectForceRegistry.h"
#include "../Objects/Particle.h"

class ParticleCollisionRegistry {
    struct ParticleCollisionEntry {
        std::shared_ptr<Particle> particleA;
        std::shared_ptr<Particle> particleB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    struct ParticleCollisionLinkEntry {
        std::shared_ptr<Particle> particleA;
        std::shared_ptr<Particle> particleB;
        float length;
    };

    std::vector<ParticleCollisionLinkEntry> RodRegistry;
    std::vector<ParticleCollisionLinkEntry> CableRegistry;
    std::vector<ParticleCollisionEntry> InterRegistry; //List of interpenetrationCollision registered

public:
    ParticleCollisionRegistry(ObjectForceRegistry* force_registry);

    void AddRodCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    void AddCableCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    void AddInterCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    //Add a collision listener between particleA and B of type interpenetrationCollision

    void CheckCollision(float duration);

private :
    void CheckRodCollision();
    void CheckCableCollision();
    void CheckInterCollision();

    void HandleCableCollision(ParticleCollisionLinkEntry& collision);
    void HandleInterCollision(ParticleCollisionEntry& collision);

    ObjectForceRegistry* force_registry;
};
