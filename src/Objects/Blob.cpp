#include "Blob.h"

#include "ofApp.h"
#include "../Force/Generators/SpringForceGenerator.h"

Blob::Blob(float x,
           float y,
           float z,
           float radius,
           float mass,
           const ofColor& color,
           float terminal_velocity,
           float spring_constant,
           float spring_rest_length) : color_(color), spring_constant_(spring_constant), spring_rest_length_(spring_rest_length) {
    if (terminal_velocity < 0) {
        throw std::invalid_argument("Terminal velocity must be greater than or equal to 0");
    }
    this->terminal_velocity_ = terminal_velocity;
    particles.push_back(make_shared<Particle>(x, y, z, radius, mass, color, terminal_velocity));
}

Blob::Blob(shared_ptr<Particle> particle, const ofColor& color, float terminal_velocity, float spring_constant, float spring_rest_length) : color_(color), spring_constant_(spring_constant), spring_rest_length_(spring_rest_length) {
    if (terminal_velocity < 0) {
        throw std::invalid_argument("Terminal velocity must be greater than or equal to 0");
    }
    this->terminal_velocity_ = terminal_velocity;
    particles.push_back(particle);
}

void Blob::update() {
    force_registry->update_forces();
    for (const auto& particle : particles) {
        particle->update();
    }
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

void Blob::fill_object_collision(std::shared_ptr<IObject> other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    const CollisionType collision_type, const float coeff) {
    for (const auto& p : particles) {
        p->fill_object_collision(other, collision_registry, collision_type, coeff);
    }
}

void Blob::fill_particle_collision(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    const CollisionType collision_type, const float coeff) {
    for (const auto& p : particles) {
        p->fill_particle_collision(particle, collision_registry, collision_type, coeff);
    }
}

void Blob::add_new_blob() { // maybe make blob a particle because we can't get the reference of the blob back after adding it to the vector
    auto new_particle = make_shared<Particle>(particles[0]->get_position().x,
                                              particles[0]->get_position().y,
                                              particles[0]->get_position().z,
                                              particles[0]->get_radius(),
                                              particles[0]->get_inv_mass(),
                                              color_,
                                              terminal_velocity_);
    particles.push_back(new_particle);
    merge(new_particle);
}

void Blob::split(shared_ptr<Particle> other)
{
    // if other is in the particle_links vector, remove it and remove the spring forces
    auto it = std::find_if(particle_links.begin(), particle_links.end(), [&other](const ParticleLink& link) {
        return link.other_particle == other;
    });

    if(it != particle_links.end()) {
        bool success1 = force_registry->remove(std::static_pointer_cast<IObject>(it->other_particle), std::static_pointer_cast<IParticleForceGenerator>(it->spring_from_to));
        bool success2 = force_registry->remove(std::static_pointer_cast<IObject>(particles[0]), std::static_pointer_cast<IParticleForceGenerator>(it->spring_to_from));
        particle_links.erase(it);
        particles.erase(std::remove(particles.begin(), particles.end(), other), particles.end());

        if(success1) {
            std::cout << "Successfully removed the spring forces" << std::endl;
        } else {
            std::cout << "Failed to remove the spring forces" << std::endl;
        }
        if(success2) {
            std::cout << "Successfully removed the spring forces" << std::endl;
        } else {
            std::cout << "Failed to remove the spring forces" << std::endl;
        }
    }
}

void Blob::merge(shared_ptr<Particle> other)
{
    const auto spring_from_to = make_shared<SpringForceGenerator>(particles[0], spring_constant_, spring_rest_length_);
    const auto spring_to_from = make_shared<SpringForceGenerator>(other, spring_constant_, spring_rest_length_);
    
    force_registry->add(particles[0], spring_to_from);
    force_registry->add(other, spring_from_to);

    const ParticleLink link = {other, spring_from_to, spring_to_from};
    particle_links.push_back(link);
    particles.push_back(other);
}

void Blob::divide()
{
    if(particles.size() <= 1) return;

    shared_ptr<Particle> newBlobParticle = particles[1];
    split(newBlobParticle);
    auto new_blob = make_shared<Blob>(newBlobParticle, color_, terminal_velocity_, spring_constant_, spring_rest_length_);

    const int division = static_cast<int>(std::round(particles.size() * 0.5f));
    std::vector<std::shared_ptr<Particle>> particles_to_split(particles.begin() + 1, particles.begin() + division);
    for (const auto& particle : particles_to_split) {
        split(particle);
        new_blob->merge(particle);
    }

    ofApp::objects_.push_back(new_blob);
}
