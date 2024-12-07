#include "Matrix3x3.h"

Matrix3x3::Matrix3x3() {
    for (auto& i : matrix_) for (float& j : i) j = 0;
}

Matrix3x3::Matrix3x3(float mat[3][3]) {
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) matrix_[i][j] = mat[i][j];
}

Matrix3x3::Matrix3x3(const Quaternion& q) {
    float qw = q.getW();
    float qx = q.getX();
    float qy = q.getY();
    float qz = q.getZ();

    matrix_[0][0] = 1 - 2 * qy * qy - 2 * qz * qz;
    matrix_[0][1] = 2 * qx * qy - 2 * qz * qw;
    matrix_[0][2] = 2 * qx * qz + 2 * qy * qw;
    matrix_[1][0] = 2 * qx * qy + 2 * qz * qw;
    matrix_[1][1] = 1 - 2 * qx * qx - 2 * qz * qz;
    matrix_[1][2] = 2 * qy * qz - 2 * qx * qw;
    matrix_[2][0] = 2 * qx * qz - 2 * qy * qw;
    matrix_[2][1] = 2 * qy * qz + 2 * qx * qw;
    matrix_[2][2] = 1 - 2 * qx * qx - 2 * qy * qy;
}

float& Matrix3x3::operator()(const int row, const int col) {
    return matrix_[row][col];
}

const float& Matrix3x3::operator()(const int row, const int col) const {
    return matrix_[row][col];
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.matrix_[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(const float scalar) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(i, j) = matrix_[i][j] * scalar;
        }
    }
    return result;
}

Matrix3x3 Matrix3x3::operator*(const Quaternion& q) const {
    Matrix3x3 result;

    // Convert quaternion to 3x3 rotation matrix
    auto rotation = Matrix3x3(q);

    // Multiply the current matrix with the rotation matrix
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(i, j) = 0;
            for (int k = 0; k < 3; ++k) {
                result(i, j) += matrix_[i][k] * rotation(k, j);
            }
        }
    }

    return result;
}

Vector Matrix3x3::operator*(const Vector& other) const {
    float values[3] = {0.f, 0.f, 0.f};
    for (int i = 0; i < 3; i++) {
        values[i] = matrix_[i][0] * other.x + matrix_[i][1] * other.y + matrix_[i][2] * other.z;
    }
    return Vector(values[0], values[1], values[2]);
}

Matrix3x3 Matrix3x3::operator/(float scalar) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(i, j) = matrix_[i][j] / scalar;
        }
    }
    return result;
}

float Matrix3x3::determinant() const {
    return matrix_[0][0] * (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) - matrix_[0][1] * (matrix_[1][0] * matrix_[2][2] - matrix_[
        1][2] * matrix_[2][0]) + matrix_[0][2] * (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]);
}

Matrix3x3 Matrix3x3::transpose() const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) result.matrix_[i][j] = matrix_[j][i];
    return result;
}

Matrix3x3 Matrix3x3::inverse() const {
    Matrix3x3 result;
    float det = determinant();

    if (det == 0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    float invDet = 1.0f / det;

    result(0, 0) = (matrix_[1][1] * matrix_[2][2] - matrix_[1][2] * matrix_[2][1]) * invDet;
    result(0, 1) = (matrix_[0][2] * matrix_[2][1] - matrix_[0][1] * matrix_[2][2]) * invDet;
    result(0, 2) = (matrix_[0][1] * matrix_[1][2] - matrix_[0][2] * matrix_[1][1]) * invDet;
    result(1, 0) = (matrix_[1][2] * matrix_[2][0] - matrix_[1][0] * matrix_[2][2]) * invDet;
    result(1, 1) = (matrix_[0][0] * matrix_[2][2] - matrix_[0][2] * matrix_[2][0]) * invDet;
    result(1, 2) = (matrix_[0][2] * matrix_[1][0] - matrix_[0][0] * matrix_[1][2]) * invDet;
    result(2, 0) = (matrix_[1][0] * matrix_[2][1] - matrix_[1][1] * matrix_[2][0]) * invDet;
    result(2, 1) = (matrix_[0][1] * matrix_[2][0] - matrix_[0][0] * matrix_[2][1]) * invDet;
    result(2, 2) = (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]) * invDet;

    return result;
}

Matrix3x3 Matrix3x3::translate(const float tx, const float ty) {
    Matrix3x3 result = identity();
    result(0, 2) = tx;
    result(1, 2) = ty;
    return result;
}

Matrix3x3 Matrix3x3::rotate(const float angle) {
    Matrix3x3 result = identity();
    const float rad = angle * PI / 180.0f;
    result(0, 0) = cos(rad);
    result(0, 1) = -sin(rad);
    result(1, 0) = sin(rad);
    result(1, 1) = cos(rad);
    return result;
}

Matrix3x3 Matrix3x3::rotateX(const float angle) {
    Matrix3x3 result = identity();
    const float rad = angle * PI / 180.0f;
    result(1, 1) = cos(rad);
    result(1, 2) = -sin(rad);
    result(2, 1) = sin(rad);
    result(2, 2) = cos(rad);
    return result;
}

Matrix3x3 Matrix3x3::rotateY(const float angle) {
    Matrix3x3 result = identity();
    const float rad = angle * PI / 180.0f;
    result(0, 0) = cos(rad);
    result(0, 2) = sin(rad);
    result(2, 0) = -sin(rad);
    result(2, 2) = cos(rad);
    return result;
}

Matrix3x3 Matrix3x3::rotateZ(const float angle) {
    Matrix3x3 result = identity();
    const float rad = angle * PI / 180.0f;
    result(0, 0) = cos(rad);
    result(0, 1) = -sin(rad);
    result(1, 0) = sin(rad);
    result(1, 1) = cos(rad);
    return result;
}

Matrix3x3 Matrix3x3::scale(const float sx, const float sy) {
    Matrix3x3 result = identity();
    result(0, 0) = sx;
    result(1, 1) = sy;
    return result;
}

Matrix3x3 Matrix3x3::identity() {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result(i, j) = (i == j) ? 1.0f : 0.0f;
        }
    }
    return result;
}
