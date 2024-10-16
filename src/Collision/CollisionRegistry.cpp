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
        Vector* posA = &(couple.particuleA->position);
        Vector* posB = &(couple.particuleB->position);
        float sq_dist = (posA.x -posB->x)*(posA.x -posB->x) + (posA.y -posB->y)*(posA.y -posB->y) + (posA.z -posB->z)*(posA.z -posB->z);

        float dist_min = couple.particuleA->radius +couple.particuleB->radius;
        dist_min = dist_min*dist_min; 
        //If there is a collision
        if(sq_dist < dist_min){
            HandleInterCollision(couple);
        }
    }
}

void CollisionRegistry::HandleInterCollision(struct ParticleCollisionEntry& collision){
    Vector normal = collision.particuleA->position - collision.particuleB->position  
    float interpdist =collision.particuleA->radius + collision.particuleB->radius - normal.magnitude() // interpenetration distance 

    


}