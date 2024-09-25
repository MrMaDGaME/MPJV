#pragma once

class Matrix3x3
{
private:
    float matrix_[3][3];

public:
    Matrix3x3();
    Matrix3x3(float mat[3][3]); // copies contents of mat into m

    float& operator()(int row, int col); // set
    const float& operator()(int row, int col) const; // get

    Matrix3x3 operator+(const Matrix3x3& other) const;
    Matrix3x3 operator-(const Matrix3x3& other) const;
    Matrix3x3 operator*(const Matrix3x3& other) const;

    [[nodiscard]] float determinant() const;
    [[nodiscard]] Matrix3x3 transpose() const;

    static Matrix3x3 translate(float tx, float ty);
    static Matrix3x3 rotate(float angle);
    static Matrix3x3 scale(float sx, float sy);
};
