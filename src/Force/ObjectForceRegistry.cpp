#include "ObjectForceRegistry.h"

void ObjectForceRegistry::add(const std::shared_ptr<IObject>& object, const std::shared_ptr<IObjectForceGenerator>& force_generator) {
    registrations_.push_back({object, force_generator});
}

void ObjectForceRegistry::add(const std::shared_ptr<IObject>& object, const std::shared_ptr<IObjectForceGenerator>& force_generator,
                              const Vector& apply_point) {
    registrations_.push_back({object, force_generator, apply_point});
}

bool ObjectForceRegistry::remove(std::shared_ptr<IObject>& object, std::shared_ptr<IObjectForceGenerator>& force_generator) {
    auto initial_size = registrations_.size();
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [object, force_generator](const ObjectForceRegistration& registration) {
                                            return registration.object == object && registration.force_generator == force_generator;
                                        }),
                         registrations_.end());
    return registrations_.size() < initial_size;
}

void ObjectForceRegistry::remove(std::shared_ptr<IObject>& object) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [object](const ObjectForceRegistration& registration) {
                                            return registration.object == object;
                                        }),
                         registrations_.end());
}

template <typename T>
void ObjectForceRegistry::remove_all_of_type(std::shared_ptr<IObject>& object) {
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [&object](const ObjectForceRegistration& registration) {
                                            return registration.object == object && dynamic_cast<T*>(registration.force_generator.get()) != nullptr;
                                        }),
                         registrations_.end());
}

void ObjectForceRegistry::clear() {
    registrations_.clear();
}

void ObjectForceRegistry::update_forces() {
    for (auto& registration : registrations_) {
        registration.force_generator->UpdateForce(registration.object, registration.apply_point);
    }
    registrations_.erase(std::remove_if(registrations_.begin(),
                                        registrations_.end(),
                                        [](ObjectForceRegistration& registration) {
                                            return dynamic_pointer_cast<ImpulseForceGenerator>(registration.force_generator) != nullptr;
                                        }),
                         registrations_.end());
}
