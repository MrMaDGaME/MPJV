#include "RigidbodyCollisionRegistry.h"
#include "../Objects/Rigidbodies/Plane.h"
#include "../Objects/Rigidbodies/Box.h"

std::vector<Vector> RigidbodyCollisionRegistry::apply_points_;

RigidbodyCollisionRegistry::RigidbodyCollisionRegistry(const std::shared_ptr<ObjectForceRegistry>& force_registry) : force_registry_(force_registry) {
}

void RigidbodyCollisionRegistry::AddInterCollision(std::shared_ptr<RigidBody> ObjectA, std::shared_ptr<RigidBody> ObjectB, float restCoeff) {
    InterRegistry.push_back({std::move(ObjectA), std::move(ObjectB), restCoeff});
}

void RigidbodyCollisionRegistry::computeInterCollisions() {
    for (const auto& couple : InterRegistry) {
        std::shared_ptr<RigidBody> objectA = couple.ObjectA;
        std::shared_ptr<RigidBody> objectB = couple.ObjectB;
        apply_points_.clear();
        auto interPDist = objectA->checkCollisionWithRigidbody(objectB);
        if (!apply_points_.empty()) {
            HandleInterCollision(couple, interPDist);
        }
    }
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Box>& box1, const std::shared_ptr<const Box>& box2) {
    return 0;
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Box>& box, const std::shared_ptr<const Plane>& plane) {
    const float box_signed_distance = plane->get_normal().dot(box->get_position() - plane->get_position());
    float interPDist_max = 0;
    for (int i = 0; i < 8; i++) {
        const Vector corner = box->get_corners()[i];
        const float corner_signed_distance = plane->get_normal().dot(corner - plane->get_position());
        Vector projection = corner - plane->get_normal() * corner_signed_distance;
        if (corner_signed_distance * box_signed_distance < 0) {
            auto proj1 = Vector(plane->get_corners()[1] - plane->get_corners()[0]).dot(Vector(projection - plane->get_corners()[0]));
            auto proj2 = Vector(plane->get_corners()[2] - plane->get_corners()[0]).dot(Vector(projection - plane->get_corners()[0]));
            if (proj1 >= 0 && proj1 <= 1 && proj2 >= 0 && proj2 <= 1) {
                interPDist_max = std::max(interPDist_max, std::abs(corner_signed_distance));
                apply_points_.push_back(projection);
            }
        }
    }
    return interPDist_max;
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Plane>& plane, const std::shared_ptr<const Box>& box) {
    return checkInterCollision(box, plane);
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Plane>& plane1, const std::shared_ptr<const Plane>& plane2) {
    return 0;
}

void RigidbodyCollisionRegistry::HandleInterCollision(const RigidBodyCollisionEntry& collision, float interPDist) {
}
