#include "ParticleForceRegistry.h"
#include "Generators/ImpulseForceGenerator.h"

void ParticleForceRegistry::add(const shared_ptr<Particle>& particle, const shared_ptr<IParticleForceGenerator>& force_generator) {
    registrations_.push_back({particle, force_generator});
}

void ParticleForceRegistry::remove(shared_ptr<Particle>& particle, shared_ptr<IParticleForceGenerator>& force_generator) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [particle, force_generator](const ParticleForceRegistration& registration) {
                                            return registration.particle == particle && registration.force_generator == force_generator;
                                        }),
                         registrations_.end());
}

void ParticleForceRegistry::remove(shared_ptr<Particle>& particle) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [particle](const ParticleForceRegistration& registration) {
                                            return registration.particle == particle;
                                        }),
                         registrations_.end());
}

void ParticleForceRegistry::clear() {
    registrations_.clear();
}

void ParticleForceRegistry::update_forces() {
    for (auto& registration : registrations_) {
        registration.force_generator->UpdateForce(registration.particle);
    }
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [](ParticleForceRegistration& registration) {
                                            return dynamic_pointer_cast<ImpulseForceGenerator>(registration.force_generator) != nullptr;
                                        }),
                         registrations_.end());
}
