#include "RigidbodyCollisionRegistry.h"
#include "../Objects/Rigidbodies/Plane.h"
#include "../Objects/Rigidbodies/Box.h"

std::vector<Vector> RigidbodyCollisionRegistry::apply_points_;

Vector RigidbodyCollisionRegistry::collision_normal_;

std::shared_ptr<ObjectForceRegistry> RigidbodyCollisionRegistry::force_registry_;


RigidbodyCollisionRegistry::RigidbodyCollisionRegistry(const std::shared_ptr<ObjectForceRegistry>& force_registry) {
    force_registry_ = force_registry;
}

void RigidbodyCollisionRegistry::AddInterCollision(std::shared_ptr<RigidBody> ObjectA, std::shared_ptr<RigidBody> ObjectB, float restCoeff) {
    InterRegistry.push_back({std::move(ObjectA), std::move(ObjectB), restCoeff});
}

void RigidbodyCollisionRegistry::computeInterCollisions() const {
    for (const auto& couple : InterRegistry) {
        std::shared_ptr<RigidBody> objectA = couple.ObjectA;
        std::shared_ptr<RigidBody> objectB = couple.ObjectB;
        const auto sphereA = objectA->get_bounding_sphere();
        const auto sphereB = objectB->get_bounding_sphere();
        if ((sphereA.getCenter() - sphereB.getCenter()).magnitude() > sphereA.getRadius() + sphereB.getRadius()) {
            continue;
        }
        collision_normal_ = {0, 0, 0};
        auto interPDist = objectA->checkCollisionWithRigidbody(objectB);
        if (!apply_points_.empty()) {
            HandleInterCollision(couple, interPDist);
        }
        apply_points_.clear();
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
            const Vector b = plane->get_corners()[3] - plane->get_corners()[0];
            const Vector c = projection - plane->get_corners()[0];
            const auto proj1 = a.dot(c) / a.magnitude();
            const auto proj2 = b.dot(c) / b.magnitude();
            if (proj1 >= 0 && proj1 <= a.magnitude() && proj2 >= 0 && proj2 <= b.magnitude()) {
                interPDist_max = std::max(interPDist_max, std::abs(corner_signed_distance));
                apply_points_.push_back(projection);
                collision_normal_ = box_signed_distance > 0 ? -plane->get_normal() : plane->get_normal();
                // collision_normal_ = plane->get_normal();
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


// apply point en coordonnée absolu point auquel appliqué la force.
//positions non modifiées
//se vident tout seul
void RigidbodyCollisionRegistry::HandleInterCollision(const RigidBodyCollisionEntry& collision, float interpDist) {
    std::shared_ptr<RigidBody> rigidBodyA = collision.ObjectA;
    std::shared_ptr<RigidBody> rigidBodyB = collision.ObjectB;
    
    Vector relativeSpeed = rigidBodyA->get_velocity() - rigidBodyB->get_velocity();
    float last_frame = static_cast<float>(ofGetLastFrameTime());
    float particuleAMass = rigidBodyA->get_inv_mass() != 0.f ? 1 / rigidBodyA->get_inv_mass() : 0;
    float particuleBMass = rigidBodyB->get_inv_mass() != 0.f ? 1 / rigidBodyB->get_inv_mass() : 0;
    float deplA = interpDist * (particuleAMass) / (particuleAMass + particuleBMass);
    rigidBodyA->set_position(rigidBodyA->get_position() + collision_normal_ * deplA);
    float deplB = interpDist * (particuleBMass) / (particuleAMass + particuleBMass);
    rigidBodyB->set_position(rigidBodyB->get_position() - collision_normal_ * deplB);
    //Check if the object is at rest on another object and if so avoid moving it.
    // if (rigidBodyA->get_velocity().magnitude() == 0.f) {
    //     if (rigidBodyB->get_velocity() * DEFAULT_GRAVITY_DIRECTION == DEFAULT_GRAVITY * last_frame) {
    //         Vector newVelocity = rigidBodyB->get_velocity() - DEFAULT_GRAVITY_DIRECTION * (rigidBodyB->get_velocity() * DEFAULT_GRAVITY_DIRECTION);
    //         //Vector newVelocity = Vector(0,0,0);
    //         rigidBodyB->set_velocity(newVelocity);
    //         return;
    //     }
    // }
    // else if (rigidBodyB->get_velocity().magnitude() == 0.f) {
    //     if (particleA->get_velocity() * DEFAULT_GRAVITY_DIRECTION == DEFAULT_GRAVITY * last_frame) {
    //         Vector newVelocity = particleA->get_velocity() - DEFAULT_GRAVITY_DIRECTION * (particleA->get_velocity() * DEFAULT_GRAVITY_DIRECTION);
    //         //Vector newVelocity = Vector(0,0,0);
    //         particleA->set_velocity(newVelocity);
    //         return;
    //     }
    // }
    float impluseValue = (collision.restCoeff + 1) * (relativeSpeed * collision_normal_) / ((rigidBodyA->get_inv_mass() + rigidBodyB->get_inv_mass()) *
        last_frame * apply_points_.size());
    for(Vector point: apply_points_){

        force_registry_->add(rigidBodyA, make_shared<ImpulseForceGenerator>(collision_normal_ * -impluseValue), point);
        force_registry_->add(rigidBodyB, make_shared<ImpulseForceGenerator>(collision_normal_ * impluseValue), point);
    }
}

void RigidbodyCollisionRegistry::clear()
{
    InterRegistry.clear();
}
