#pragma once
#include <cmath>
#include "Quaternion.h"
#include <glm/glm.hpp>

#include "ofMatrix4x4.h"

class Matrix4x4 {
public:
    Matrix4x4();
    Matrix4x4(float mat[4][4]);
    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;
    Matrix4x4 operator+(const Matrix4x4& other) const;
    Matrix4x4 operator-(const Matrix4x4& other) const;
    Matrix4x4 operator*(const Matrix4x4& other) const;
    Matrix4x4 operator*(float scalar) const;
    Matrix4x4 operator*(const Quaternion& q) const;
    Matrix4x4 operator/(float scalar) const;
    [[nodiscard]] float determinant() const;
    [[nodiscard]] Matrix4x4 transpose() const;
    [[nodiscard]] Matrix4x4 inverse() const;
    static Matrix4x4 translate(float tx, float ty, float tz);
    static Matrix4x4 rotate(float angle, float x, float y, float z);
    static Matrix4x4 rotateX(float angle);
    static Matrix4x4 rotateY(float angle);
    static Matrix4x4 rotateZ(float angle);
    static Matrix4x4 scale(float sx, float sy, float sz);
    static Matrix4x4 identity();

    [[nodiscard]] glm::mat4 to_glm() const;
    [[nodiscard]] ofMatrix4x4 ToOfMatrix() const;
    
    
private:
    float matrix_[4][4];
};
