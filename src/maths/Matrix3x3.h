#pragma once
#include "ofMathConstants.h"
#include <cmath>
#include "Quaternion.h"
#include "Vector.h"

class Matrix3x3 {
public:
    Matrix3x3();
    Matrix3x3(float mat[3][3]); // copies contents of mat into m
    Matrix3x3(const Quaternion& q);
    float& operator()(int row, int col); // set
    const float& operator()(int row, int col) const; // get
    Matrix3x3 operator+(const Matrix3x3& other) const;
    Matrix3x3 operator-(const Matrix3x3& other) const;
    Matrix3x3 operator*(const Matrix3x3& other) const;
    Matrix3x3 operator*(float scalar) const;
    Matrix3x3 operator*(const Quaternion& q) const;
    Vector operator*(const Vector& other) const;
    Matrix3x3 operator/(float scalar) const;
    [[nodiscard]] float determinant() const;
    [[nodiscard]] Matrix3x3 transpose() const;
    [[nodiscard]] Matrix3x3 inverse() const;
    static Matrix3x3 translate(float tx, float ty);
    static Matrix3x3 rotate(float angle);
    static Matrix3x3 rotateX(float angle);
    static Matrix3x3 rotateY(float angle);
    static Matrix3x3 rotateZ(float angle);
    static Matrix3x3 scale(float sx, float sy);
    static Matrix3x3 identity();
    static Matrix3x3 null();

private:
    float matrix_[3][3];
};
