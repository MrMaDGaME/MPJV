#include "ocTree.h"

ocTree::ocTree(const Vector& center, const Vector& halfSize, int depth, int maxDepth, int maxBodies)
    : center_(center), halfSize_(halfSize), depth_(depth), maxDepth_(maxDepth), maxBodies_(maxBodies) {}

ocTree::ocTree(const Vector& center, const float halfSize, int depth, int maxDepth, int maxBodies) 
    : center_(center), halfSize_(Vector(halfSize, halfSize, halfSize)), depth_(depth), maxDepth_(maxDepth), maxBodies_(maxBodies) {}

void ocTree::insert(std::shared_ptr<RigidBody> body) {
    if (!isLeaf()) {
        auto octants = getOctants(body->get_position(), body->getBoundingSphere().getRadius());
        for (int octant : octants) {
            if (!children_[octant]) {
                Vector newCenter = center_;
                newCenter.x += (octant & 4 ? 0.25f : -0.25f) * halfSize_.x;
                newCenter.y += (octant & 2 ? 0.25f : -0.25f) * halfSize_.y;
                newCenter.z += (octant & 1 ? 0.25f : -0.25f) * halfSize_.z;
                children_[octant] = std::make_unique<ocTree>(newCenter, halfSize_ * 0.5f, depth_ + 1, maxDepth_, maxBodies_);
            }
            children_[octant]->insert(body);
        }
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
            if (child && overlaps(regionCenter, regionHalfSize, child->center_, child->halfSize_.magnitude())) {
                auto childResult = child->query(regionCenter, regionHalfSize);
                result.insert(result.end(), childResult.begin(), childResult.end());
            }
        }
    } else {
        for (const auto& body : bodies_) {
            const Vector& pos = body->get_position();
            float radius = body->getBoundingSphere().getRadius();
            if (overlaps(regionCenter, regionHalfSize, pos, radius)) {
                result.push_back(body);
            }
        }
    }
    return result;
}

std::set<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> ocTree::getAllPairs() const {
    std::set<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> pairs;
    getAllPairsHelper(pairs);
    return pairs;
}

void ocTree::draw() const {
    ofSetColor(ofColor::blueSteel);
    drawBox(center_, halfSize_);
    if (!isLeaf()) {
        for (const auto& child : children_) {
            if (child) {
                child->draw();
            }
        }
    }
}

void ocTree::getAllPairsHelper(std::set<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>>& pairs) const {
    if (!isLeaf()) {
        for (const auto& child : children_) {
            if (child) {
                child->getAllPairsHelper(pairs);
            }
        }
    } else {
        for (size_t currentBodyIndex = 0; currentBodyIndex < bodies_.size(); ++currentBodyIndex) {
            for (size_t otherBodyIndex = 0; otherBodyIndex < bodies_.size(); ++otherBodyIndex) {
                if (currentBodyIndex != otherBodyIndex) {
                    auto pair = std::make_pair(bodies_[currentBodyIndex], bodies_[otherBodyIndex]);
                    auto reversePair = std::make_pair(bodies_[otherBodyIndex], bodies_[currentBodyIndex]);
                    if (pairs.find(reversePair) == pairs.end()) {
                        pairs.insert(pair);
                    }
                }
            }
        }
    }
}

void ocTree::drawBox(const Vector& center, const Vector& halfSize) const
{
    // Calculate the 8 corners of the box
    Vector corners[8];
    for (int i = 0; i < 8; ++i) {
        corners[i] = center;
        corners[i].x += (i & 4 ? 0.5f : -0.5f) * halfSize.x;
        corners[i].y += (i & 2 ? 0.5f : -0.5f) * halfSize.y;
        corners[i].z += (i & 1 ? 0.5f : -0.5f) * halfSize.z;
    }

    // Draw the 12 edges of the box
    ofDrawLine(corners[0].x, corners[0].y, corners[0].z, corners[1].x, corners[1].y, corners[1].z);
    ofDrawLine(corners[1].x, corners[1].y, corners[1].z, corners[3].x, corners[3].y, corners[3].z);
    ofDrawLine(corners[3].x, corners[3].y, corners[3].z, corners[2].x, corners[2].y, corners[2].z);
    ofDrawLine(corners[2].x, corners[2].y, corners[2].z, corners[0].x, corners[0].y, corners[0].z);

    ofDrawLine(corners[4].x, corners[4].y, corners[4].z, corners[5].x, corners[5].y, corners[5].z);
    ofDrawLine(corners[5].x, corners[5].y, corners[5].z, corners[7].x, corners[7].y, corners[7].z);
    ofDrawLine(corners[7].x, corners[7].y, corners[7].z, corners[6].x, corners[6].y, corners[6].z);
    ofDrawLine(corners[6].x, corners[6].y, corners[6].z, corners[4].x, corners[4].y, corners[4].z);

    ofDrawLine(corners[0].x, corners[0].y, corners[0].z, corners[4].x, corners[4].y, corners[4].z);
    ofDrawLine(corners[1].x, corners[1].y, corners[1].z, corners[5].x, corners[5].y, corners[5].z);
    ofDrawLine(corners[2].x, corners[2].y, corners[2].z, corners[6].x, corners[6].y, corners[6].z);
    ofDrawLine(corners[3].x, corners[3].y, corners[3].z, corners[7].x, corners[7].y, corners[7].z);
}

bool ocTree::isLeaf() const {
    return children_.empty();
}

void ocTree::subdivide() {
    children_.resize(8);
    for (const auto& body : bodies_) {
        auto octants = getOctants(body->get_position(), body->getBoundingSphere().getRadius());
        for (int octant : octants) {
            if (!children_[octant]) {
                Vector newCenter = center_;
                newCenter.x += (octant & 4 ? 0.25f : -0.25f) * halfSize_.x;
                newCenter.y += (octant & 2 ? 0.25f : -0.25f) * halfSize_.y;
                newCenter.z += (octant & 1 ? 0.25f : -0.25f) * halfSize_.z;
                children_[octant] = std::make_unique<ocTree>(newCenter, halfSize_ * 0.5f, depth_ + 1, maxDepth_, maxBodies_);
            }
            children_[octant]->insert(body);
        }
    }
    bodies_.clear();
}

std::vector<int> ocTree::getOctants(const Vector& point, const float radius) const {
    std::vector<int> octants;
    for (int i = 0; i < 8; ++i) {
        Vector newCenter = center_;
        newCenter.x += (i & 4 ? 0.25f : -0.25f) * halfSize_.x;
        newCenter.y += (i & 2 ? 0.25f : -0.25f) * halfSize_.y;
        newCenter.z += (i & 1 ? 0.25f : -0.25f) * halfSize_.z;
        if (overlaps(newCenter, halfSize_ * 0.5f, point, radius)) {
            octants.push_back(i);
        }
    }
    return octants;
}

bool ocTree::overlaps(const Vector& regionCenter, const Vector& regionHalfSize, const Vector& point, float radius) const {
    return (point.x + radius >= regionCenter.x - regionHalfSize.x && point.x - radius <= regionCenter.x + regionHalfSize.x &&
            point.y + radius >= regionCenter.y - regionHalfSize.y && point.y - radius <= regionCenter.y + regionHalfSize.y &&
            point.z + radius >= regionCenter.z - regionHalfSize.z && point.z - radius <= regionCenter.z + regionHalfSize.z);
}