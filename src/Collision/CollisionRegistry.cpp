#include "CollisionRegistry.h"

void CollisionRegistry::AddRodCollision(Particle* particleA, Particle* particleB){
    RodRegistry.push_back({ particleA, particleB });
}
void CollisionRegistry::AddCableCollision(Particle* particleA, Particle* particleB, float length){
    CableRegistry.push_back({ particleA, particleB, length});
}
void CollisionRegistry::AddInterCollision(Particle* particleA, Particle* particleB,float length)//Add a collision listener between particleA and B of type interpenetration
{
    InterRegistry.push_back({ particleA, particleB, length });
}

void CollisionRegistry::CheckCollision(float duration){
    CheckRodCollision();
    CheckCableCollision();
    CheckInterCollision();
}


void CollisionRegistry::CheckRodCollision(){
    for(auto couple: RodRegistry){
        
    }
}
void CollisionRegistry::ChekCableCollision(){

}
void CollisionRegistry::CheckInterCollision(){
    for(auto couple: InterRegistry){
        Vector* posA = &(couple.particleA->position);
        Vector* posB = &(couple.particleB->position);
        float sq_dist = (posA.x -posB->x)*(posA.x -posB->x) + (posA.y -posB->y)*(posA.y -posB->y) + (posA.z -posB->z)*(posA.z -posB->z);

        float dist_min = couple.particleA->radius +couple.particleB->radius;
        dist_min = dist_min*dist_min; 
        //If there is a collision
        if(sq_dist < dist_min){
            HandleInterCollision(couple);
        }
    }
}

void CollisionRegistry::HandleInterCollision(struct ParticleCollisionEntry& collision){
    Particle particleA = collision.particleA;
    Particle particleB = collision.partic
    
    Vector normal = particleA->position - particleB->position;


    float interpdist =particleA->radius + particleB->radius - normal.magnitude(); // interpenetration distance 

    normal.normalize(); //normal length set to 1


    Vector relativeSpeed = particleA->velocity - particleB->velocity;

    float impluseValue = (collision.restCoeff + 1) * (relativeSpeed*normal)/(particleA.inv_mass + particleB.inv_mass);

    float deplA = interpdist* (1/particleA.inv_mass)/((1/particleA.inv_mass)+(1/particleB.inv_mass))

    particleA.position += normal * deplA;

    float deplB = interpdist*(1/particleB.inv_mass)/((1/particleA.inv_mass)+(1/particleB.inv_mass))

    particleB.position -= normal * deplB;

    
}


    


}