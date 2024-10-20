#pragma once
#include "../Objects/IObject.h"
#include "../Force/ObjectForceRegistry.h"

class ParticleCollisionRegistry {
    struct ParticleCollisionEntry {
        shared_ptr<IObject> particleA;
        shared_ptr<IObject> particleB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    struct ParticleCollisionLinkEntry {
        shared_ptr<IObject> particleA;
        shared_ptr<IObject> particleB;
        float length;
    };

    std::vector<ParticleCollisionLinkEntry> RodRegistry;
    std::vector<ParticleCollisionLinkEntry> CableRegistry;
    std::vector<ParticleCollisionEntry> InterRegistry; //List of interpenetrationCollision registered

public:
    ParticleCollisionRegistry(ObjectForceRegistry* force_registry);

    void AddRodCollision(shared_ptr<IObject>& particleA, shared_ptr<IObject>& particleB, float length);
    void AddCableCollision(shared_ptr<IObject>& particleA, shared_ptr<IObject>& particleB, float length);
    void AddInterCollision(shared_ptr<IObject>& particleA, shared_ptr<IObject>& particleB, float length);
    //Add a collision listener between particleA and B of type interpenetrationCollision

    void CheckCollision(float duration);

private :
    void CheckRodCollision();
    void CheckCableCollision();
    void CheckInterCollision();

    void HandleInterCollision(ParticleCollisionEntry& collision);

    ObjectForceRegistry* force_registry;
};
