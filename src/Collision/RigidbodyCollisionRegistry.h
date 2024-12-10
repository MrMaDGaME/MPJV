#pragma once

#include <vector>

#include "../Force/ObjectForceRegistry.h"

class RigidBody;
class Box;
class Plane;

class RigidbodyCollisionRegistry : public std::enable_shared_from_this<RigidbodyCollisionRegistry> {
    struct RigidBodyCollisionEntry { //Struct used to store an interpenetration collision Checked in CheckCollision
        std::shared_ptr<RigidBody> ObjectA;
        std::shared_ptr<RigidBody> ObjectB;
        float restCoeff; //coefficient of restitution give the elasticity of collision : 0 perfectly inelastic, 1 perfectly elastic
    };

    std::vector<RigidBodyCollisionEntry> InterRegistry; //List of interpenetrationCollision registered

public:
    RigidbodyCollisionRegistry(const std::shared_ptr<ObjectForceRegistry>& force_registry);

    void AddInterCollision(std::shared_ptr<RigidBody> ObjectA, std::shared_ptr<RigidBody> ObjectB, float restCoeff);
    //Add a collision listener between particleA and B of type interpenetrationCollision

    //Call adapted Handler in case of collision
    void computeInterCollisions() const;
    static float checkInterCollision(const std::shared_ptr<const Box>& box1, const std::shared_ptr<const Box>& box2);
    static float checkInterCollision(const std::shared_ptr<const Box>& box, const std::shared_ptr<const Plane>& plane);
    static float checkInterCollision(const std::shared_ptr<const Plane>& plane, const std::shared_ptr<const Box>& box);
    static float checkInterCollision(const std::shared_ptr<const Plane>& plane1, const std::shared_ptr<const Plane>& plane2);

    static void HandleInterCollision(const RigidBodyCollisionEntry& collision, float interPDist);

private:
    static std::vector<Vector> apply_points_;
    static Vector collision_normal_;
    static std::shared_ptr<ObjectForceRegistry> force_registry_;
};
