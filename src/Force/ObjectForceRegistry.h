#pragma once
#include "IObjectForceGenerator.h"
#include "../Objects/IObject.h"
#include "Generators/ImpulseForceGenerator.h"

class ObjectForceRegistry {
    struct ObjectForceRegistration {
        std::shared_ptr<IObject> object;
        std::shared_ptr<IObjectForceGenerator> force_generator;
        Vector apply_point = {0, 0, 0};
    };

public:
    void add(const std::shared_ptr<IObject>& object, const std::shared_ptr<IObjectForceGenerator>& force_generator);
    void add(const std::shared_ptr<IObject>& object, const std::shared_ptr<IObjectForceGenerator>& force_generator, const Vector& apply_point);
    bool remove(std::shared_ptr<IObject>& object, std::shared_ptr<IObjectForceGenerator>& force_generator);
    void remove(std::shared_ptr<IObject>& object);

    template <typename T>
    void remove_all_of_type(std::shared_ptr<IObject>& object);

    void clear();
    void update_forces();

    std::vector<ObjectForceRegistration> registrations_;
};
