#include "ParticleCollisionRegistry.h"

ParticleCollisionRegistry::ParticleCollisionRegistry(ObjectForceRegistry *force_registry)
{ this->force_registry = force_registry;
}

void ParticleCollisionRegistry::AddRodCollision(shared_ptr<Particle>& particleA,shared_ptr<Particle>& particleB)
{
    RodRegistry.push_back({ particleA, particleB });
}
void ParticleCollisionRegistry::AddCableCollision(shared_ptr<Particle>& particleA, shared_ptr<Particle>& particleB, float length){
    CableRegistry.push_back({ particleA, particleB, length});
}
void ParticleCollisionRegistry::AddInterCollision(shared_ptr<Particle>& particleA, shared_ptr<Particle>& particleB,float length)//Add a collision listener between particleA and B of type interpenetration
{
    InterRegistry.push_back({ particleA, particleB, length });
}

void ParticleCollisionRegistry::CheckCollision(float duration){
    CheckRodCollision();
    CheckCableCollision();
    CheckInterCollision();
}


void ParticleCollisionRegistry::CheckRodCollision(){
    for(auto couple: RodRegistry){
        
    }
}
void ParticleCollisionRegistry::CheckCableCollision(){

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

void ParticleCollisionRegistry::HandleInterCollision(struct ParticleCollisionEntry& collision){
    shared_ptr<Particle>& particleA = collision.particleA;
    shared_ptr<Particle>& particleB = collision.particleB; 

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


    


