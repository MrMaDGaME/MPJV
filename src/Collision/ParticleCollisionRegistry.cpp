#include "ParticleCollisionRegistry.h"

ParticleCollisionRegistry::ParticleCollisionRegistry(ObjectForceRegistry *force_registry)
{ this->force_registry = force_registry;
}

void ParticleCollisionRegistry::AddRodCollision(std::shared_ptr<Particle> particleA,std::shared_ptr<Particle> particleB, float length)
{
    RodRegistry.push_back({ particleA, particleB, length});
}
void ParticleCollisionRegistry::AddCableCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB, float length){
    CableRegistry.push_back({ particleA, particleB, length});
}
void ParticleCollisionRegistry::AddInterCollision(std::shared_ptr<Particle> particleA, std::shared_ptr<Particle> particleB,float restCoeff)//Add a collision listener between particleA and B of type interpenetration
{
    InterRegistry.push_back({ particleA, particleB, restCoeff });
}

void ParticleCollisionRegistry::CheckCollision(float duration){
    CheckRodCollision();
    CheckCableCollision();
    CheckInterCollision();
}


void ParticleCollisionRegistry::CheckRodCollision(){
    for(auto couple: RodRegistry){
        Vector posA = couple.particleA->get_position();
        Vector posB = couple.particleB->get_position();
        float sq_dist = (posA.x -posB.x)*(posA.x -posB.x) + (posA.y -posB.y)*(posA.y -posB.y) + (posA.z -posB.z)*(posA.z -posB.z);

        float dist_rod = couple.length;
        dist_rod = dist_rod*dist_rod;

        if(sq_dist != dist_rod){
            HandleRodCollision(couple);
        }
    }
}
void ParticleCollisionRegistry::CheckCableCollision(){
    for(auto couple : CableRegistry){
        Vector posA = couple.particleA->get_position();
        Vector posB = couple.particleB->get_position();
        float sq_dist = (posA.x -posB.x)*(posA.x -posB.x) + (posA.y -posB.y)*(posA.y -posB.y) + (posA.z -posB.z)*(posA.z -posB.z);

        float dist_max = couple.length;
        dist_max = dist_max*dist_max;

        if(sq_dist > dist_max){
            HandleCableCollision(couple);
        }
    }
}
void ParticleCollisionRegistry::CheckInterCollision(){
    for(auto couple: InterRegistry){
        Vector posA = couple.particleA->get_position();
        Vector posB = couple.particleB->get_position();
        float sq_dist = (posA.x -posB.x)*(posA.x -posB.x) + (posA.y -posB.y)*(posA.y -posB.y) + (posA.z -posB.z)*(posA.z -posB.z);

        float dist_min = couple.particleA->get_radius() +couple.particleB->get_radius();
        dist_min = dist_min*dist_min; 
        //If there is a collision
        if(sq_dist < dist_min){
            HandleInterCollision(couple);
        }
    }
}

void HandleRodCollision(ParticleCollisionLinkEntry& collision){
    std::shared_ptr<Particle>& particleA = collision.particleA;
    std::shared_ptr<Particle>& particleB = collision.particleB;

    Vector normal = particleA->get_position() - particleB->get_position();


    float interpdist = normal.magnitude() - collision.length; // interpenetration distance 

    normal.normalize(); //normal length set to 1

    Vector relativeSpeed = particleA->get_velocity() - particleB->get_velocity();

    float impluseValue = (relativeSpeed*normal)/(particleA->get_inv_mass() + particleB->get_inv_mass());

    float deplA = interpdist* (1/particleA->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleA->set_position(particleA->get_position() - normal * deplA);

    float deplB = interpdist*(1/particleB->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleB->set_position(particleB->get_position() + normal * deplB);

    force_registry->add(particleA,make_shared<ImpulseForceGenerator>(normal*-impluseValue));
    force_registry->add(particleB,make_shared<ImpulseForceGenerator>(normal*impluseValue));
}


void ParticleCollisionRegistry::HandleCableCollision(ParticleCollisionLinkEntry& collision){
    std::shared_ptr<Particle>& particleA = collision.particleA;
    std::shared_ptr<Particle>& particleB = collision.particleB;

    Vector normal = particleA->get_position() - particleB->get_position();


    float interpdist = normal.magnitude() - collision.length; // interpenetration distance 

    normal.normalize(); //normal length set to 1

    Vector relativeSpeed = particleA->get_velocity() - particleB->get_velocity();

    float impluseValue = (relativeSpeed*normal)/(particleA->get_inv_mass() + particleB->get_inv_mass());

    float deplA = interpdist* (1/particleA->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleA->set_position(particleA->get_position() - normal * deplA);

    float deplB = interpdist*(1/particleB->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleB->set_position(particleB->get_position() + normal * deplB);

    force_registry->add(particleA,make_shared<ImpulseForceGenerator>(normal*-impluseValue));
    force_registry->add(particleB,make_shared<ImpulseForceGenerator>(normal*impluseValue));
}

void ParticleCollisionRegistry::HandleInterCollision(ParticleCollisionEntry& collision){
    std::shared_ptr<Particle>& particleA = collision.particleA;
    std::shared_ptr<Particle>& particleB = collision.particleB;

    Vector normal = particleA->get_position() - particleB->get_position();


    float interpdist =particleA->get_radius() + particleB->get_radius() - normal.magnitude(); // interpenetration distance 

    normal.normalize(); //normal length set to 1


    Vector relativeSpeed = particleA->get_velocity() - particleB->get_velocity();

    float impluseValue = (collision.restCoeff + 1) * (relativeSpeed*normal)/(particleA->get_inv_mass() + particleB->get_inv_mass());

    float deplA = interpdist* (1/particleA->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleA->set_position(particleA->get_position() + normal * deplA);

    float deplB = interpdist*(1/particleB->get_inv_mass())/((1/particleA->get_inv_mass())+(1/particleB->get_inv_mass()));

    particleB->set_position(particleB->get_position() - normal * deplB);

    force_registry->add(particleA,make_shared<ImpulseForceGenerator>(normal*-impluseValue));
    force_registry->add(particleB,make_shared<ImpulseForceGenerator>(normal*-impluseValue));


}


    


