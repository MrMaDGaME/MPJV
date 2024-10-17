#include "../Particle.h"
#include "../Force/IParticleForceGenerator.h"
class CollisionRegistry
{
private:
    struct ParticleCollisionEntry
    {
        Particle* particleA;
        Particle* particleB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    struct ParticleCollisionLinkEntry
    {  
        Particle* particleA;
        Particle* particleB;
        float length;

    }
    std::vector<ParticleCollisionEntry> RodRegistry;
    std::vector<ParticleCollisionLinkEntry> CableRegistry;
    std::vector<ParticleCollisionLinkEntry> InterRegistry;//List of interpenetrationCollision registered

    

public:
    void AddRodCollision(Particle* particleA, Particle* particleB);
    void AddCableCollision(Particle* particleA, Particle* particleB, float length);
    void AddInterCollision(Particle* particleA, Particle* particleB, float length);//Add a collision listener between particleA and B of type interpenetrationCollision

    void CheckCollision(float duration);
private :
    void CheckRodCollision();
    void ChekCableCollision();
    void CheckInterCollision();

    void HandleInterCollision(struct ParticleCollisionEntry& collision);
};
