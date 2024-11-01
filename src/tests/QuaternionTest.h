#pragma once

#include "../maths/Quaternion.h"
#include "VectorTests.h"
#include <iostream>

class QuaternionTest {
public:
    // Test du constructeur par défaut
    static void testDefaultConstructor() {
        Quaternion q;
        assertEqual(q.getW(), 1.0, "testDefaultConstructor - w");
        assertEqual(q.getX(), 0.0, "testDefaultConstructor - x");
        assertEqual(q.getY(), 0.0, "testDefaultConstructor - y");
        assertEqual(q.getZ(), 0.0, "testDefaultConstructor - z");
    }

    // Test du constructeur avec arguments
    static void testConstructorWithArgs() {
        Quaternion q(1.0, 2.0, 3.0, 4.0);
        assertEqual(q.getW(), 1.0, "testConstructorWithArgs - w");
        assertEqual(q.getX(), 2.0, "testConstructorWithArgs - x");
        assertEqual(q.getY(), 3.0, "testConstructorWithArgs - y");
        assertEqual(q.getZ(), 4.0, "testConstructorWithArgs - z");
    }

    // Test de l'addition de deux quaternions
    static void testAddition() {
        Quaternion q1(1.0, 2.0, 3.0, 4.0);
        Quaternion q2(4.0, 3.0, 2.0, 1.0);
        Quaternion result = q1 + q2;
        assertEqual(result.getW(), 5.0, "testAddition - w");
        assertEqual(result.getX(), 5.0, "testAddition - x");
        assertEqual(result.getY(), 5.0, "testAddition - y");
        assertEqual(result.getZ(), 5.0, "testAddition - z");
    }

    // Test de la soustraction de deux quaternions
    static void testSubtraction() {
        Quaternion q1(4.0, 5.0, 6.0, 7.0);
        Quaternion q2(1.0, 2.0, 3.0, 4.0);
        Quaternion result = q1 - q2;
        assertEqual(result.getW(), 3.0, "testSubtraction - w");
        assertEqual(result.getX(), 3.0, "testSubtraction - x");
        assertEqual(result.getY(), 3.0, "testSubtraction - y");
        assertEqual(result.getZ(), 3.0, "testSubtraction - z");
    }

    // Test de la multiplication par un scalaire
    static void testScalarMultiplication() {
        Quaternion q(1.0, 2.0, 3.0, 4.0);
        Quaternion result = q * 2.0;
        assertEqual(result.getW(), 2.0, "testScalarMultiplication - w");
        assertEqual(result.getX(), 4.0, "testScalarMultiplication - x");
        assertEqual(result.getY(), 6.0, "testScalarMultiplication - y");
        assertEqual(result.getZ(), 8.0, "testScalarMultiplication - z");
    }

    // Test de la norme d'un quaternion
    static void testNorm() {
        Quaternion q(1.0, 2.0, 2.0, 1.0);
        float result = q.norm();
        assertEqual(result, 3.16228f, "testNorm");
    }

    // Test de la conjugaison
    static void testConjugate() {
        Quaternion q(1.0, 2.0, 3.0, 4.0);
        Quaternion result = q.conjugate();
        assertEqual(result.getW(), 1.0, "testConjugate - w");
        assertEqual(result.getX(), -2.0, "testConjugate - x");
        assertEqual(result.getY(), -3.0, "testConjugate - y");
        assertEqual(result.getZ(), -4.0, "testConjugate - z");
    }

    // Test de la normalisation
    static void testNormalize() {
        Quaternion q(0.0, 3.0, 4.0, 0.0);
        q.normalize();
        assertEqual(q.getW(), 0.0, "testNormalize - w");
        assertEqual(q.getX(), 0.6, "testNormalize - x");
        assertEqual(q.getY(), 0.8, "testNormalize - y");
        assertEqual(q.getZ(), 0.0, "testNormalize - z");
    }

    // Lancer tous les tests
    static void runAllTests() {
        std::cout << "Running quaternion tests..." << std::endl;
        testDefaultConstructor();
        testConstructorWithArgs();
        testAddition();
        testSubtraction();
        testScalarMultiplication();
        testNorm();
        testConjugate();
        testNormalize();
        std::cout << "Quaternion tests finished." << std::endl;
    }
};
