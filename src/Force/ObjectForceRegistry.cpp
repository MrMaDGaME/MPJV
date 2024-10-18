#include "ObjectForceRegistry.h"

void ObjectForceRegistry::add(const shared_ptr<IObject>& object, const shared_ptr<IParticleForceGenerator>& force_generator) {
    registrations_.push_back({object, force_generator});
}

void ObjectForceRegistry::remove(shared_ptr<IObject>& object, shared_ptr<IParticleForceGenerator>& force_generator) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [object, force_generator](const ParticleForceRegistration& registration) {
                                            return registration.object == object && registration.force_generator == force_generator;
                                        }),
                         registrations_.end());
}

void ObjectForceRegistry::remove(shared_ptr<IObject>& object) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [object](const ParticleForceRegistration& registration) {
                                            return registration.object == object;
                                        }),
                         registrations_.end());
}

void ObjectForceRegistry::clear() {
    registrations_.clear();
}

void ObjectForceRegistry::update_forces() {
    for (auto& registration : registrations_) {
        registration.force_generator->UpdateForce(registration.object);
    }
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [](ParticleForceRegistration& registration) {
                                            return dynamic_pointer_cast<ImpulseForceGenerator>(registration.force_generator) != nullptr;
                                        }),
                         registrations_.end());
}
