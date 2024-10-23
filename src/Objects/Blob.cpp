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
           float spring_rest_length) : color_(color), spring_constant_(spring_constant), spring_rest_length_(spring_rest_length), displayedParticleCount_(1)  {
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
    for(auto& particle : particles) {
        particle->addForce(force);
    }
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

void Blob::set_inv_mass(const float inv_mass) {
    particles[0]->set_inv_mass(inv_mass);
}

void Blob::fill_object_collision(std::shared_ptr<IObject> other, std::shared_ptr<ParticleCollisionRegistry>& collision_registry,
    const CollisionType collision_type, const float coeff) {
    this->collision_registry = collision_registry;
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
    const auto new_particle = make_shared<Particle>(particles[0]->get_position().x,
                                                    particles[0]->get_position().y,
                                                    particles[0]->get_position().z,
                                                    particles[0]->get_radius(),
                                                    particles[0]->get_inv_mass(),
                                                    color_,
                                                    terminal_velocity_);
    for (shared_ptr<IObject> other : ofApp::objects_){
        if (other.get() != this){
            std::cout << "NOT GO DABDABOOM \n";
        }else{
            std::cout << "OK SAME BLOB \n";
        }
    }
    merge(new_particle);
}

void Blob::split(const shared_ptr<Particle>& other)
{
    remove_all_links(other);
    particles.erase(std::remove(particles.begin(), particles.end(), other), particles.end());
}

void Blob::merge(const shared_ptr<Particle>& other)
{
    particles.push_back(other);
    refresh_springs();
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

void Blob::add_link(shared_ptr<Particle> p1, shared_ptr<Particle> p2)
{
    const auto spring_from_to = make_shared<SpringForceGenerator>(p1, spring_constant_, spring_rest_length_);
    const auto spring_to_from = make_shared<SpringForceGenerator>(p2, spring_constant_, spring_rest_length_);

    force_registry->add(p1, spring_to_from);
    force_registry->add(p2, spring_from_to);

    const ParticleLink link = {p1, p2, spring_from_to, spring_to_from};
    particle_links.push_back(link);
}

void Blob::remove_all_links(shared_ptr<Particle> p) {
    // Collect links to be removed
    std::vector<ParticleLink> links_to_remove;
    for (const auto& link : particle_links) {
        if (link.p1 == p || link.p2 == p) {
            links_to_remove.push_back(link);
        }
    }

    // Remove the spring forces
    for (const auto& link : links_to_remove) {
        force_registry->remove(std::static_pointer_cast<IObject>(link.p2), std::static_pointer_cast<IParticleForceGenerator>(link.spring_from_to));
        force_registry->remove(std::static_pointer_cast<IObject>(link.p1), std::static_pointer_cast<IParticleForceGenerator>(link.spring_to_from));
    }

    // Erase the links from the particle_links vector
    particle_links.erase(std::remove_if(particle_links.begin(), particle_links.end(), [&p](const ParticleLink& link) {
        return link.p1 == p || link.p2 == p;
    }), particle_links.end());
}

void Blob::refresh_springs()
{
    // remove all links, then for each particle other than the main one, add a link between the main particle and the other particle, and the other and the previous, and the other and the next % particles.size()
    for(const auto& particle : particles) {
        remove_all_links(particle);
    }
    
    for(int i = 1; i < particles.size(); i++) {
        add_link(particles[0], particles[i]);
        add_link(particles[i], particles[(i - 1) % particles.size()]);

        if(i == particles.size() - 1) {
            add_link(particles[i], particles[1]);
        }
        else
        {
            add_link(particles[i], particles[(i + 1)]);
        }
    }
}

int Blob::get_particle_count() const {
    return particles.size();
}
