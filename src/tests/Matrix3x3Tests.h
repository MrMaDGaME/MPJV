#pragma once

#include "../maths/Matrix3x3.h"
#include "VectorTests.h"
#include <iostream>

class Matrix3x3Tests {
public:
    // Test du constructeur par défaut
    static void testDefaultConstructor() {
        Matrix3x3 m;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(m(i, j), 0.0f, "testDefaultConstructor");
            }
        }
    }

    // Test du constructeur avec arguments
    static void testConstructorWithArgs() {
        float mat[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        Matrix3x3 m(mat);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(m(i, j), mat[i][j], "testConstructorWithArgs");
            }
        }
    }

    // Test de l'addition de deux matrices
    static void testAddition() {
        float mat1[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        float mat2[3][3] = {{9.0f, 8.0f, 7.0f}, {6.0f, 5.0f, 4.0f}, {3.0f, 2.0f, 1.0f}};
        Matrix3x3 m1(mat1);
        Matrix3x3 m2(mat2);
        Matrix3x3 result = m1 + m2;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(result(i, j), mat1[i][j] + mat2[i][j], "testAddition");
            }
        }
    }

    // Test de la soustraction de deux matrices
    static void testSubtraction() {
        float mat1[3][3] = {{9.0f, 8.0f, 7.0f}, {6.0f, 5.0f, 4.0f}, {3.0f, 2.0f, 1.0f}};
        float mat2[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        Matrix3x3 m1(mat1);
        Matrix3x3 m2(mat2);
        Matrix3x3 result = m1 - m2;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(result(i, j), mat1[i][j] - mat2[i][j], "testSubtraction");
            }
        }
    }

    // Test de la multiplication de deux matrices
    static void testMultiplication() {
        float mat1[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        float mat2[3][3] = {{9.0f, 8.0f, 7.0f}, {6.0f, 5.0f, 4.0f}, {3.0f, 2.0f, 1.0f}};
        Matrix3x3 m1(mat1);
        Matrix3x3 m2(mat2);
        Matrix3x3 result = m1 * m2;
        float expected[3][3] = {
            {30.0f, 24.0f, 18.0f},
            {84.0f, 69.0f, 54.0f},
            {138.0f, 114.0f, 90.0f}
        };
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(result(i, j), expected[i][j], "testMultiplication");
            }
        }
    }

    // Test de la transposition d'une matrice
    static void testTranspose() {
        float mat[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        Matrix3x3 m(mat);
        Matrix3x3 result = m.transpose();
        float expected[3][3] = {{1.0f, 4.0f, 7.0f}, {2.0f, 5.0f, 8.0f}, {3.0f, 6.0f, 9.0f}};
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                assertEqual(result(i, j), expected[i][j], "testTranspose");
            }
        }
    }

    // Test de la détermination d'une matrice
    static void testDeterminant() {
        float mat[3][3] = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
        Matrix3x3 m(mat);
        float result = m.determinant();
        assertEqual(result, 0.0f, "testDeterminant");
    }

    // Lancer tous les tests
    static void runAllTests() {
        std::cout << "Running Matrix3x3 tests..." << std::endl;
        testDefaultConstructor();
        testConstructorWithArgs();
        testAddition();
        testSubtraction();
        testMultiplication();
        testTranspose();
        testDeterminant();
        std::cout << "Matrix3x3 tests finished." << std::endl;
    }
};