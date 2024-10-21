#include "Blob.h"

#include "../Force/Generators/SpringForceGenerator.h"

Blob::Blob(float x,
           float y,
           float z,
           float radius,
           float mass,
           const ofColor& color,
           float terminal_velocity,
           float spring_constant,
           float spring_rest_length) : color_(color), spring_constant_(spring_constant), spring_rest_length_(spring_rest_length),particleCount_(1), displayedParticleCount_(1)  {
    if (terminal_velocity < 0) {
        throw std::invalid_argument("Terminal velocity must be greater than or equal to 0");
    }
    this->terminal_velocity_ = terminal_velocity;
    particles.push_back(make_shared<Particle>(x, y, z, radius, mass, color, terminal_velocity));
}

void Blob::update() {
    force_registry->update_forces();

    // Mettre à jour les particules
    for (const auto& particle : particles) {
        particle->update();
    }

    // Calculer la vitesse moyenne de toutes les particules
    Vector averageVelocity(0, 0, 0);
    for (const auto& particle : particles) {
        averageVelocity += particle->get_velocity();
    }
    averageVelocity /= static_cast<float>(particles.size());

    // Limiter la vitesse globale si elle dépasse la vitesse terminale
    if (averageVelocity.magnitude() > terminal_velocity_) {
        averageVelocity = averageVelocity.normalize() * terminal_velocity_;
    }

    // Appliquer la vitesse limitée à toutes les particules
    for (const auto& particle : particles) {
        particle->set_velocity(averageVelocity);
    }

    // Mettre à jour le compteur de particules affiché
    displayedParticleCount_ += (particles.size() - displayedParticleCount_) * animationSpeed;
    displayedParticleCount_ *= dampingFactor;
}


void Blob::draw() {
    for (const auto& particle : particles) {
        particle->draw();
    }
}

void Blob::addForce(const Vector& force) {
    particles[0]->addForce(force);
}

Vector Blob::get_position() const {
    return particles[0]->get_position();
}

void Blob::set_position(const Vector& position) {
    particles[0]->set_position(position);
}

Vector Blob::get_velocity() const {
    return particles[0]->get_velocity();
}

void Blob::set_velocity(const Vector& velocity) {
    particles[0]->set_velocity(velocity);
}

float Blob::get_inv_mass() const {
    return particles[0]->get_inv_mass();
}

void Blob::set_inv_mass(float inv_mass) {
    particles[0]->set_inv_mass(inv_mass);
}

void Blob::split() {
    auto new_particle = make_shared<Particle>(particles[0]->get_position().x,
                                              particles[0]->get_position().y,
                                              particles[0]->get_position().z,
                                              particles[0]->get_radius(),
                                              particles[0]->get_inv_mass(),
                                              color_,
                                              terminal_velocity_);
    particles.push_back(new_particle);
    force_registry->add(new_particle, make_shared<SpringForceGenerator>(particles[0], spring_constant_, spring_rest_length_));
    force_registry->add(particles[0], make_shared<SpringForceGenerator>(new_particle, spring_constant_, spring_rest_length_));
}

int Blob::get_particle_count() const {
    return particles.size();
}
