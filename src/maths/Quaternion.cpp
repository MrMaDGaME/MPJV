#include "Quaternion.h"

// Constructeurs
Quaternion::Quaternion() : w(1), x(0), y(0), z(0) {
}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {
}

// Méthodes pour accéder aux composantes
float Quaternion::getW() const { return w; }
float Quaternion::getX() const { return x; }
float Quaternion::getY() const { return y; }
float Quaternion::getZ() const { return z; }

// Opérateurs
Quaternion Quaternion::operator+(const Quaternion& q) const {
    return {w + q.w, x + q.x, y + q.y, z + q.z};
}

Quaternion Quaternion::operator-(const Quaternion& q) const {
    return {w - q.w, x - q.x, y - q.y, z - q.z};
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    float newW = w * q.w - x * q.x - y * q.y - z * q.z;
    float newX = w * q.x + x * q.w + y * q.z - z * q.y;
    float newY = w * q.y - x * q.z + y * q.w + z * q.x;
    float newZ = w * q.z + x * q.y - y * q.x + z * q.w;
    return {newW, newX, newY, newZ};
}

Quaternion Quaternion::operator*(float scalar) const {
    return {w * scalar, x * scalar, y * scalar, z * scalar};
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
    if (this != &q) {
        w = q.w;
        x = q.x;
        y = q.y;
        z = q.z;
    }
    return *this;
}

// Méthodes supplémentaires
float Quaternion::norm() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::conjugate() const {
    return {w, -x, -y, -z};
}

Quaternion Quaternion::inverse() const {
    float normSq = w * w + x * x + y * y + z * z;
    if (normSq == 0) {
        throw std::runtime_error("Division par zéro : le quaternion n'a pas d'inverse.");
    }
    return conjugate() * (1.f / normSq);
}

void Quaternion::normalize() {
    float n = norm();
    if (n == 0) {
        throw std::runtime_error("Impossible de normaliser un quaternion de norme nulle.");
    }
    w /= n;
    x /= n;
    y /= n;
    z /= n;
}

Matrix4x4 Quaternion::ToMatrix() const {
    // Convert quaternion to 4x4 rotation matrix
    Matrix4x4 rotation = Matrix4x4::identity();
    rotation(0, 0) = 1 - 2 * y * y - 2 * z * z;
    rotation(0, 1) = 2 * x * y - 2 * z * w;
    rotation(0, 2) = 2 * x * z + 2 * y * w;
    rotation(1, 0) = 2 * x * y + 2 * z * w;
    rotation(1, 1) = 1 - 2 * x * x - 2 * z * z;
    rotation(1, 2) = 2 * y * z - 2 * x * w;
    rotation(2, 0) = 2 * x * z - 2 * y * w;
    rotation(2, 1) = 2 * y * z + 2 * x * w;
    rotation(2, 2) = 1 - 2 * x * x - 2 * y * y;

    return rotation;
}

// Affichage
void Quaternion::print() const {
    std::cout << "(" << w << ", " << x << ", " << y << ", " << z << ")" << std::endl;
}
