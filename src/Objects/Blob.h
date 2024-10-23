#pragma once
#include "Particle.h"
#include "../Force/ObjectForceRegistry.h"
#include "Force/Generators/SpringForceGenerator.h"

class Blob : public IObject {
    struct ParticleLink {
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
    CollisionType collision_type, float coeff) override;
    void fill_particle_collision(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    CollisionType collision_type, float coeff) override;

    void add_new_blob();
    void split(const shared_ptr<Particle>& other);
    void merge(const shared_ptr<Particle>& other);
    void merge(shared_ptr<Blob>& other);
    void divide();
    void add_link(shared_ptr<Particle> p1, shared_ptr<Particle> p2);
    void remove_all_links(shared_ptr<Particle> p);
    void refresh_springs();
    shared_ptr<Blob> get_nearest_blob() const;
    void merge_with_nearest_blob();
    int get_particle_count() const;


    std::vector<shared_ptr<Particle>> particles; // 0 is the main particle
    std::vector<ParticleLink> particle_links; // 0 and 1 == 1 in particles, 2 and 3 == 2 in particles, etc.
private:
    ofColor color_;
    float terminal_velocity_;
    shared_ptr<ObjectForceRegistry> force_registry = make_shared<ObjectForceRegistry>();
    shared_ptr<ParticleCollisionRegistry> collision_registry;
    float spring_constant_;
    float spring_rest_length_;
    
    // Attributs pour le compteur de particules
    float displayedParticleCount_; // Compteur de particules affiché avec animation
    float animationSpeed = 0.8f; // Vitesse de l'animation
    float dampingFactor = 0.9f; // Facteur d'amortissement
    Vector position_;

};
