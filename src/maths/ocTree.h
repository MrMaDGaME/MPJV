#pragma once

#include <vector>
#include <memory>

#include "Vector.h"
#include "Objects/Rigidbodies/RigidBody.h"

class ocTree {
public:
    ocTree(const Vector& center, const Vector& halfSize, int depth = 0, int maxDepth = 5, int maxBodies = 8);
    void insert(std::shared_ptr<RigidBody> body);
    void clear();
    std::vector<std::shared_ptr<RigidBody>> query(const Vector& regionCenter, const Vector& regionHalfSize) const;
private:
    Vector center_;
    Vector halfSize_;
    int depth_;
    int maxDepth_;
    int maxBodies_;
    std::vector<std::shared_ptr<RigidBody>> bodies_;
    std::vector<std::unique_ptr<ocTree>> children_;

    bool isLeaf() const;
    void subdivide();
    int getOctant(const Vector& point) const;
};
