#pragma once
#include "../Objects/Particle.h"
#include "../Force/IParticleForceGenerator.h"
#include "../Force/ObjectForceRegistry.h"

class ParticleCollisionRegistry
{
private:
    struct ParticleCollisionEntry
    {
        shared_ptr<Particle> particleA;
        shared_ptr<Particle> particleB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    struct ParticleCollisionLinkEntry
    {  
        shared_ptr<Particle> particleA;
        shared_ptr<Particle> particleB;
        float length;

    };
    std::vector<ParticleCollisionLinkEntry> RodRegistry;
    std::vector<ParticleCollisionLinkEntry> CableRegistry;
    std::vector<ParticleCollisionEntry> InterRegistry;//List of interpenetrationCollision registered

    

public:

    ParticleCollisionRegistry(ObjectForceRegistry* force_registry);

    void AddRodCollision(shared_ptr<Particle>& particleA, shared_ptr<Particle>& particleB);
    void AddCableCollision(shared_ptr<Particle>& particleA, shared_ptr<Particle>& particleB, float length);
    void AddInterCollision(shared_ptr<Particle>& particleA, shared_ptr<Particle>& particleB, float length);//Add a collision listener between particleA and B of type interpenetrationCollision

    void CheckCollision(float duration);
private :
    void CheckRodCollision();
    void CheckCableCollision();
    void CheckInterCollision();

    void HandleInterCollision(struct ParticleCollisionEntry& collision);


private :
    ObjectForceRegistry* force_registry;
};
