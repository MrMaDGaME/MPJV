#pragma once
#include "Particle.h"
#include "../Force/ObjectForceRegistry.h"

class Blob : public IObject {
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

    void update() override;
    void draw() override;
    void addForce(const Vector& force) override;
    [[nodiscard]] Vector get_position() const override;
    void set_position(const Vector& position) override;
    [[nodiscard]] Vector get_velocity() const override;
    void set_velocity(const Vector& velocity) override;
    [[nodiscard]] float get_inv_mass() const override;
    void set_inv_mass(float inv_mass) override;

    void split();
    int get_particle_count() const;
    
private:
    std::vector<shared_ptr<Particle>> particles;

    ofColor color_;
    float terminal_velocity_;
    shared_ptr<ObjectForceRegistry> force_registry = make_shared<ObjectForceRegistry>();
    float spring_constant_;
    float spring_rest_length_;
    
    int particleCount_; // Nombre de particules attachées au Blob
    // Attributs pour le compteur de particules
    float displayedParticleCount_; // Compteur de particules affiché avec animation
    float animationSpeed = 0.8f; // Vitesse de l'animation
    float dampingFactor = 0.9f; // Facteur d'amortissement
    Vector position_;

};
