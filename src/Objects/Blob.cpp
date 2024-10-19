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
           float spring_rest_length) : color_(color), spring_constant_(spring_constant), spring_rest_length_(spring_rest_length) {
    if (terminal_velocity < 0) {
        throw std::invalid_argument("Terminal velocity must be greater than or equal to 0");
    }
    this->terminal_velocity_ = terminal_velocity;
    particles.push_back(make_shared<Particle>(x, y, z, radius, mass, color, terminal_velocity));
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

void Blob::set_global_force_registry(shared_ptr<ObjectForceRegistry> global_ptr){
    particle[0]->global_force_registry.swap(global_ptr);
}

shared_ptr<ObjectForceRegistry> Blob::get_global_force_registry(){
    return Particle[0]->get_global_force_registry();
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
