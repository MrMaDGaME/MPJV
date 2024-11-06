#include "Matrix4x4.h"

#include "Matrix3x3.h"
#include "ofMathConstants.h"

Matrix4x4::Matrix4x4() {
    for (auto& i : matrix_) for (float& j : i) j = 0;
}

Matrix4x4::Matrix4x4(float mat[4][4]) {
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) matrix_[i][j] = mat[i][j];
}

float& Matrix4x4::operator()(const int row, const int col) {
    return matrix_[row][col];
}

const float& Matrix4x4::operator()(const int row, const int col) const {
    return matrix_[row][col];
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.matrix_[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    return result;
}

float Matrix4x4::determinant() const {
    float det = 0.0f;
    for (int i = 0; i < 4; ++i) {
        Matrix3x3 subMatrix;
        for (int j = 1; j < 4; ++j) {
            int subCol = 0;
            for (int k = 0; k < 4; ++k) {
                if (k == i) continue;
                subMatrix(j - 1, subCol) = matrix_[j][k];
                ++subCol;
            }
        }
        float subDet = subMatrix.determinant();
        det += (i % 2 == 0 ? 1 : -1) * matrix_[0][i] * subDet;
    }
    return det;
}

Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) result.matrix_[i][j] = matrix_[j][i];
    return result;
}

Matrix4x4 Matrix4x4::translate(const float tx, const float ty, const float tz) {
    Matrix4x4 result = identity(); // Initialize as identity matrix
    result(0, 3) = tx;
    result(1, 3) = ty;
    result(2, 3) = tz;
    return result;
}

Matrix4x4 Matrix4x4::rotate(const float angle, const float x, const float y, const float z) {
    Matrix4x4 result = identity(); // Initialize as identity matrix
    const float rad = angle * PI / 180.0f;
    const float c = cos(rad);
    const float s = sin(rad);
    const float t = 1 - c;

    result(0, 0) = t * x * x + c;
    result(0, 1) = t * x * y - s * z;
    result(0, 2) = t * x * z + s * y;
    result(1, 0) = t * x * y + s * z;
    result(1, 1) = t * y * y + c;
    result(1, 2) = t * y * z - s * x;
    result(2, 0) = t * x * z - s * y;
    result(2, 1) = t * y * z + s * x;
    result(2, 2) = t * z * z + c;

    return result;
}

Matrix4x4 Matrix4x4::rotateX(float angle) {
    Matrix4x4 result = identity();
    float rad = angle * PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    result(1, 1) = c;
    result(1, 2) = -s;
    result(2, 1) = s;
    result(2, 2) = c;

    return result;
}

Matrix4x4 Matrix4x4::rotateY(float angle) {
    Matrix4x4 result = identity();
    float rad = angle * PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    result(0, 0) = c;
    result(0, 2) = s;
    result(2, 0) = -s;
    result(2, 2) = c;

    return result;
}

Matrix4x4 Matrix4x4::rotateZ(float angle) {
    Matrix4x4 result = identity();
    float rad = angle * PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    result(0, 0) = c;
    result(0, 1) = -s;
    result(1, 0) = s;
    result(1, 1) = c;

    return result;
}

Matrix4x4 Matrix4x4::scale(const float sx, const float sy, const float sz) {
    Matrix4x4 result = identity();
    result(0, 0) = sx;
    result(1, 1) = sy;
    result(2, 2) = sz;
    return result;
}

Matrix4x4 Matrix4x4::identity() {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = (i == j) ? 1.0f : 0.0f;
        }
    }
    return result;
}