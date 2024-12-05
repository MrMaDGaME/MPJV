#pragma once

#include "../Force/ObjectForceRegistry.h"
#include "../Force/Generators/GravityForceGenerator.h"
#include "../Objects/Particle.h"

class ParticleCollisionRegistry {
    struct ParticleCollisionEntry { //Struct used to store an interpenetration collision Checked in CheckCollision
        std::shared_ptr<Particle> particleA;
        std::shared_ptr<Particle> particleB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    struct ParticleCollisionLinkEntry { //Struct used to store a cable or rod collision Checked in CheckCollision 
        std::shared_ptr<Particle> particleA;
        std::shared_ptr<Particle> particleB;
        float length;
    };

    std::vector<ParticleCollisionLinkEntry> RodRegistry; //List of RodCollision registered
    std::vector<ParticleCollisionLinkEntry> CableRegistry; // List of CableCollision registered
    std::vector<ParticleCollisionEntry> InterRegistry; //List of interpenetrationCollision registered

public:
    ParticleCollisionRegistry(shared_ptr<ObjectForceRegistry> force_registry);

    void AddRodCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    //Add a collision listener between particleA and B of type RodCollision
    void AddCableCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    //Add a collision listener between particleA and B of type CableCollision
    void AddInterCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length);
    //Add a collision listener between particleA and B of type interpenetrationCollision

    void RemoveCableCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB); //Delete a listener of type CableCollision

    void CheckCollision(float duration);
    //Iterate on all Collision's listeners to check if there is a collision. The argument is the time since last frame for debugging purpose.

private :
    //Call adapted Handler in case of collision
    void CheckRodCollision();
    void CheckCableCollision();
    void CheckInterCollision();

    void HandleRodCollision(ParticleCollisionLinkEntry& collision);
    void HandleCableCollision(ParticleCollisionLinkEntry& collision);
    void HandleInterCollision(ParticleCollisionEntry& collision);

    std::shared_ptr<ObjectForceRegistry> force_registry;
};
