#include "RigidbodyCollisionRegistry.h"
#include "../Objects/Rigidbodies/Plane.h"
#include "../Objects/Rigidbodies/Box.h"

std::vector<Vector> RigidbodyCollisionRegistry::apply_points_;

Vector RigidbodyCollisionRegistry::collision_normal_;

RigidbodyCollisionRegistry::RigidbodyCollisionRegistry(const std::shared_ptr<ObjectForceRegistry>& force_registry) : force_registry_(force_registry) {
}

void RigidbodyCollisionRegistry::AddInterCollision(std::shared_ptr<RigidBody> ObjectA, std::shared_ptr<RigidBody> ObjectB, float restCoeff) {
    InterRegistry.push_back({std::move(ObjectA), std::move(ObjectB), restCoeff});
}

void RigidbodyCollisionRegistry::computeInterCollisions() const {
    for (const auto& couple : InterRegistry) {
        std::shared_ptr<RigidBody> objectA = couple.ObjectA;
        std::shared_ptr<RigidBody> objectB = couple.ObjectB;
        apply_points_.clear();
        collision_normal_ = {0, 0, 0};
        auto interPDist = objectA->checkCollisionWithRigidbody(objectB);
        if (!apply_points_.empty()) {
            std::cout << "Collision detected" << std::endl;
            HandleInterCollision(couple, interPDist);
        }
    }
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Box>& box1, const std::shared_ptr<const Box>& box2) {
    // iteration sur les faces de la box2
    using Face = std::array<int, 4>;
    const std::vector<Face> faces = {
        {0, 1, 2, 3}, // Face gauche
        {4, 5, 6, 7}, // Face droite
        {0, 1, 5, 4}, // Face bas
        {2, 3, 7, 6}, // Face haut
        {0, 3, 7, 4}, // Face arrière
        {1, 2, 6, 5} // Face avant
    };
    for (const auto& face : faces) {
        std::vector<glm::vec3> face_corners(4);
        for (int i = 0; i < 4; i++) {
            face_corners[i] = box2->get_corners()[face[i]];
        }
        auto face_plane = std::make_shared<Plane>(face_corners);
        face_plane->set_normal();
        const auto interPDist = checkInterCollision(box1, face_plane);
        if (!apply_points_.empty()) {
            return interPDist;
        }
    }
    return 0;
}

float RigidbodyCollisionRegistry::checkInterCollision(const std::shared_ptr<const Box>& box, const std::shared_ptr<const Plane>& plane) {
    const float box_signed_distance = plane->get_normal().dot(box->get_position() - plane->get_position());
    float interPDist_max = 0;
    for (int i = 0; i < 8; i++) {
        const Vector corner = box->get_corners()[i];
        const float corner_signed_distance = plane->get_normal().dot(corner - plane->get_position());
        const Vector projection = corner - plane->get_normal() * corner_signed_distance;
        if (corner_signed_distance * box_signed_distance < 0) {
            const Vector a = plane->get_corners()[1] - plane->get_corners()[0];
            const Vector b = plane->get_corners()[2] - plane->get_corners()[0];
            const Vector c = projection - plane->get_corners()[0];
            const auto proj1 = a.dot(c) / a.magnitude();
            const auto proj2 = b.dot(c) / b.magnitude();
            if (proj1 >= 0 && proj1 <= a.magnitude() && proj2 >= 0 && proj2 <= b.magnitude()) {
                interPDist_max = std::max(interPDist_max, std::abs(corner_signed_distance));
                apply_points_.push_back(projection);
                collision_normal_ = plane->get_normal();
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
