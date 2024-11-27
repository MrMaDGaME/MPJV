#include "ocTree.h"

ocTree::ocTree(const Vector& center, const Vector& halfSize, int depth, int maxDepth, int maxBodies)
    : center_(center), halfSize_(halfSize), depth_(depth), maxDepth_(maxDepth), maxBodies_(maxBodies) {}

void ocTree::insert(std::shared_ptr<RigidBody> body) {
    if (!isLeaf()) {
        int octant = getOctant(body->get_position());
        if (!children_[octant]) {
            Vector newCenter = center_;
            newCenter.x += (octant & 4 ? 0.5f : -0.5f) * halfSize_.x;
            newCenter.y += (octant & 2 ? 0.5f : -0.5f) * halfSize_.y;
            newCenter.z += (octant & 1 ? 0.5f : -0.5f) * halfSize_.z;
            children_[octant] = std::make_unique<ocTree>(newCenter, halfSize_ * 0.5f, depth_ + 1, maxDepth_, maxBodies_);
        }
        children_[octant]->insert(body);
    } else {
        bodies_.push_back(body);
        if (bodies_.size() > maxBodies_ && depth_ < maxDepth_) {
            subdivide();
        }
    }
}

void ocTree::clear() {
    bodies_.clear();
    children_.clear();
}

std::vector<std::shared_ptr<RigidBody>> ocTree::query(const Vector& regionCenter, const Vector& regionHalfSize) const {
    std::vector<std::shared_ptr<RigidBody>> result;
    if (!isLeaf()) {
        for (const auto& child : children_) {
            if (child) {
                auto childResult = child->query(regionCenter, regionHalfSize);
                result.insert(result.end(), childResult.begin(), childResult.end());
            }
        }
    } else {
        for (const auto& body : bodies_) {
            const Vector& pos = body->get_position();
            if (pos.x >= regionCenter.x - regionHalfSize.x && pos.x <= regionCenter.x + regionHalfSize.x &&
                pos.y >= regionCenter.y - regionHalfSize.y && pos.y <= regionCenter.y + regionHalfSize.y &&
                pos.z >= regionCenter.z - regionHalfSize.z && pos.z <= regionCenter.z + regionHalfSize.z) {
                result.push_back(body);
            }
        }
    }
    return result;
}

bool ocTree::isLeaf() const {
    return children_.empty();
}

void ocTree::subdivide() {
    children_.resize(8);
    for (const auto& body : bodies_) {
        int octant = getOctant(body->get_position());
        if (!children_[octant]) {
            Vector newCenter = center_;
            newCenter.x += (octant & 4 ? 0.5f : -0.5f) * halfSize_.x;
            newCenter.y += (octant & 2 ? 0.5f : -0.5f) * halfSize_.y;
            newCenter.z += (octant & 1 ? 0.5f : -0.5f) * halfSize_.z;
            children_[octant] = std::make_unique<ocTree>(newCenter, halfSize_ * 0.5f, depth_ + 1, maxDepth_, maxBodies_);
        }
        children_[octant]->insert(body);
    }
    bodies_.clear();
}

int ocTree::getOctant(const Vector& point) const // Return the octant in which the point is located (the "zone" of the point)
{
    int octant = 0;
    if (point.x >= center_.x) octant |= 4;
    if (point.y >= center_.y) octant |= 2;
    if (point.z >= center_.z) octant |= 1; 
    return octant;
}