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
    const Vector box1_to_box2 = box2->get_position() - box1->get_position();
    const float x_overlap = box1->get_width() / 2 + box2->get_width() / 2 - std::abs(box1_to_box2.x);
    const float y_overlap = box1->get_height() / 2 + box2->get_height() / 2 - std::abs(box1_to_box2.y);
    const float z_overlap = box1->get_depth() / 2 + box2->get_depth() / 2 - std::abs(box1_to_box2.z);
    if (x_overlap > 0 && y_overlap > 0 && z_overlap > 0) {
        const float min_overlap = std::min({x_overlap, y_overlap, z_overlap});
        const Vector normal = box1_to_box2.getNormal();
        apply_points_.push_back(box1->get_position() + normal * box1->get_width() / 2);
        apply_points_.push_back(box1->get_position() - normal * box1->get_width() / 2);
        apply_points_.push_back(box2->get_position() + normal * box2->get_width() / 2);
        apply_points_.push_back(box2->get_position() - normal * box2->get_width() / 2);
        return min_overlap;
    }
    return 0;
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Box>& box, const std::shared_ptr<const Plane>& plane) {
    const float box_signed_distance = plane->get_normal().dot(box->get_position() - plane->get_position());
    float interPDist_max = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                const Vector corner = box->get_position() + Vector(static_cast<float>(i) * box->get_width(),
                                                                   static_cast<float>(j) * box->get_height(),
                                                                   static_cast<float>(k) * box->get_depth());
                const float corner_signed_distance = plane->get_normal().dot(corner - plane->get_position());
                const Vector projection = corner - plane->get_normal() * corner_signed_distance;
                if (corner_signed_distance * box_signed_distance < 0) {
                    interPDist_max = std::max(interPDist_max, std::abs(corner_signed_distance));
                    apply_points_.push_back(corner);
                }
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
