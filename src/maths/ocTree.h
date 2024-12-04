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
    [[nodiscard]] std::vector<std::shared_ptr<RigidBody>> query(const Vector& regionCenter, const Vector& regionHalfSize) const; // returns all bodies in the region, the region's shape is a box
    [[nodiscard]] std::set<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> getAllPairs() const; // returns all pairs of bodies that are in the same region
    
    
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
    std::vector<int> getOctants(const Vector& point, float radius) const;
    bool overlaps(const Vector& regionCenter, const Vector& regionHalfSize, const Vector& point, float radius) const;
    void getAllPairsHelper(std::set<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>>& pairs) const;

};