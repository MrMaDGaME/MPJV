#pragma once

#include "../maths/Matrix4x4.h"
#include "VectorTests.h"
#include <iostream>

class Matrix4x4Tests {
public:
    // Test du constructeur par défaut
    static void testDefaultConstructor() {
        Matrix4x4 m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(m(i, j), 0.0f, "testDefaultConstructor");
            }
        }
    }

    // Test du constructeur avec arguments
    static void testConstructorWithArgs() {
        float mat[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        Matrix4x4 m(mat);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(m(i, j), mat[i][j], "testConstructorWithArgs");
            }
        }
    }

    // Test de l'addition de deux matrices
    static void testAddition() {
        float mat1[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        float mat2[4][4] = {{16.0f, 15.0f, 14.0f, 13.0f}, {12.0f, 11.0f, 10.0f, 9.0f}, {8.0f, 7.0f, 6.0f, 5.0f}, {4.0f, 3.0f, 2.0f, 1.0f}};
        Matrix4x4 m1(mat1);
        Matrix4x4 m2(mat2);
        Matrix4x4 result = m1 + m2;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(result(i, j), mat1[i][j] + mat2[i][j], "testAddition");
            }
        }
    }

    // Test de la soustraction de deux matrices
    static void testSubtraction() {
        float mat1[4][4] = {{16.0f, 15.0f, 14.0f, 13.0f}, {12.0f, 11.0f, 10.0f, 9.0f}, {8.0f, 7.0f, 6.0f, 5.0f}, {4.0f, 3.0f, 2.0f, 1.0f}};
        float mat2[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        Matrix4x4 m1(mat1);
        Matrix4x4 m2(mat2);
        Matrix4x4 result = m1 - m2;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(result(i, j), mat1[i][j] - mat2[i][j], "testSubtraction");
            }
        }
    }

    // Test de la multiplication de deux matrices
    static void testMultiplication() {
        float mat1[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        float mat2[4][4] = {{16.0f, 15.0f, 14.0f, 13.0f}, {12.0f, 11.0f, 10.0f, 9.0f}, {8.0f, 7.0f, 6.0f, 5.0f}, {4.0f, 3.0f, 2.0f, 1.0f}};
        Matrix4x4 m1(mat1);
        Matrix4x4 m2(mat2);
        Matrix4x4 result = m1 * m2;
        float expected[4][4] = {
            {80.0f, 70.0f, 60.0f, 50.0f}, {240.0f, 214.0f, 188.0f, 162.0f}, {400.0f, 358.0f, 316.0f, 274.0f}, {560.0f, 502.0f, 444.0f, 386.0f}
        };
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(result(i, j), expected[i][j], "testMultiplication");
            }
        }
    }

    // Test de la transposition d'une matrice
    static void testTranspose() {
        float mat[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        Matrix4x4 m(mat);
        Matrix4x4 result = m.transpose();
        float expected[4][4] = {{1.0f, 5.0f, 9.0f, 13.0f}, {2.0f, 6.0f, 10.0f, 14.0f}, {3.0f, 7.0f, 11.0f, 15.0f}, {4.0f, 8.0f, 12.0f, 16.0f}};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                assertEqual(result(i, j), expected[i][j], "testTranspose");
            }
        }
    }

    // Test du determinant d'une matrice
    static void testDeterminant() {
        float mat[4][4] = {{1.0f, 2.0f, 3.0f, 4.0f}, {5.0f, 6.0f, 7.0f, 8.0f}, {9.0f, 10.0f, 11.0f, 12.0f}, {13.0f, 14.0f, 15.0f, 16.0f}};
        Matrix4x4 m(mat);
        float result = m.determinant();
        assertEqual(result, 0.0f, "testDeterminant");
    }

    // Lancer tous les tests
    static void runAllTests() {
        std::cout << "Running Matrix4x4 tests..." << std::endl;
        testDefaultConstructor();
        testConstructorWithArgs();
        testAddition();
        testSubtraction();
        testMultiplication();
        testTranspose();
        testDeterminant();
        std::cout << "Matrix4x4 tests finished." << std::endl;
    }
};
