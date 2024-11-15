﻿#pragma once

class Matrix4x4;
class Matrix3x3;

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
    [[nodiscard]] Matrix4x4 ToMatrix4() const;
    [[nodiscard]] Matrix3x3 ToMatrix3() const;

    // Affichage
    void print() const;

private:
    float w, x, y, z;
};
