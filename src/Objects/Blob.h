#pragma once
#include "Particle.h"
#include "../Force/ObjectForceRegistry.h"
#include "Force/Generators/SpringForceGenerator.h"

class Blob : public IObject {
    struct ParticleLink { // A link between two particles
        shared_ptr<Particle> p1;
        shared_ptr<Particle> p2;
        shared_ptr<SpringForceGenerator> spring_from_to;
        shared_ptr<SpringForceGenerator> spring_to_from;
    };
    

public:
    Blob(float x,
         float y,
         float z,
         float radius,
         float mass,
         const ofColor& color,
         float terminal_velocity,
         float spring_constant,
         float spring_rest_length);

    Blob(shared_ptr<Particle> particle, const ofColor& color, float terminal_velocity, float spring_constant, float spring_rest_length);

    void update() override;
    void draw() override;
    void addForce(const Vector& force) override;
    [[nodiscard]] Vector get_position() const override;
    void set_position(const Vector& position) override;
    [[nodiscard]] Vector get_velocity() const override;
    void set_velocity(const Vector& velocity) override;
    [[nodiscard]] float get_inv_mass() const override;
    void set_inv_mass(float inv_mass) override;
    void fill_object_collision(std::shared_ptr<IObject> other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    CollisionType collision_type, float coeff) override; // Initiates the collisions with other objects for all the particles in the blob
    void fill_particle_collision(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    CollisionType collision_type, float coeff) override;

    void add_new_blob(); // Spawns a particle and merges it with the blob
    void split(const shared_ptr<Particle>& other); // Removes the particle from the blob
    void merge(const shared_ptr<Particle>& other); // Adds the particle to the blob
    void merge(shared_ptr<Blob>& other); // Splits all the particles from the other blob and merges them with this blob, also deletes the other blob
    void divide(); // Splits the blob into two blobs
    void add_link(shared_ptr<Particle> p1, shared_ptr<Particle> p2); // Creates a link between two particles
    void remove_all_links(shared_ptr<Particle> p); // Removes all links from a particle
    void refresh_springs(); // Destroy all links and create new ones
    shared_ptr<Blob> get_nearest_blob() const; // Returns the nearest blob
    void merge_with_nearest_blob(); // Merges with the nearest blob if there is one
    int get_particle_count() const;


    std::vector<shared_ptr<Particle>> particles; // 0 is the main particle
    std::vector<ParticleLink> particle_links; // All the links between particles in the blob
    shared_ptr<ParticleCollisionRegistry> collision_registry; // A reference to the global collision registry
private:
    ofColor color_;
    float terminal_velocity_;
    shared_ptr<ObjectForceRegistry> force_registry = make_shared<ObjectForceRegistry>();
    
    float spring_constant_;
    float spring_rest_length_;
    Vector position_;
};
