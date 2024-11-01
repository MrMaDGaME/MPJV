#pragma once

#include <iostream>
#include <cmath>

class Quaternion {
public:
    // Constructeurs
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    // Méthodes pour accéder aux composantes
    [[nodiscard]] float getW() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getZ() const;

    // Opérateurs
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float scalar) const;
    Quaternion& operator=(const Quaternion& q);

    // Méthodes supplémentaires
    [[nodiscard]] float norm() const;
    [[nodiscard]] Quaternion conjugate() const;
    [[nodiscard]] Quaternion inverse() const;
    void normalize();

    // Affichage
    void print() const;

private:
    float w, x, y, z;
};
