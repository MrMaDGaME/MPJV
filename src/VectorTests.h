#pragma once
#include <iostream>
#include "Vector.h"
// Fonction utilitaire pour vérifier les assertions
inline void assertEqual(float a, float b, const std::string& testName) {
    if (abs(a - b) > 1e-5) {
        // tolérance pour les flottants
        std::cerr << "[FAIL] " << testName << ": attendu " << b << ", obtenu " << a << std::endl;
        exit(1);
    }
    else {
        std::cout << "[PASS] " << testName << std::endl;
    }
}

inline void assertTrue(bool condition, const std::string& testName) {
    if (!condition) {
        std::cerr << "[FAIL] " << testName << ": condition fausse." << std::endl;
        exit(1);
    }
    else {
        std::cout << "[PASS] " << testName << std::endl;
    }
}

// Classe de test pour Vector
class VectorTest {
public:
    // Test du constructeur avec deux arguments
    static void testConstructorWithTwoArgs() {
        Vector v(1.0f, 2.0f);
        assertEqual(v.x, 1.0f, "testConstructorWithTwoArgs - x");
        assertEqual(v.y, 2.0f, "testConstructorWithTwoArgs - y");
        assertEqual(v.z, 0.0f, "testConstructorWithTwoArgs - z");
    }

    // Test de l'addition de deux vecteurs
    static void testAddition() {
        Vector v1(1.0f, 2.0f, 3.0f);
        Vector v2(4.0f, 5.0f, 6.0f);
        Vector result = v1 + v2;
        assertEqual(result.x, 5.0f, "testAddition - x");
        assertEqual(result.y, 7.0f, "testAddition - y");
        assertEqual(result.z, 9.0f, "testAddition - z");
    }

    // Test de la soustraction de deux vecteurs
    static void testSubtraction() {
        Vector v1(4.0f, 5.0f, 6.0f);
        Vector v2(1.0f, 2.0f, 3.0f);
        Vector result = v1 - v2;
        assertEqual(result.x, 3.0f, "testSubtraction - x");
        assertEqual(result.y, 3.0f, "testSubtraction - y");
        assertEqual(result.z, 3.0f, "testSubtraction - z");
    }

    // Test de la multiplication par un scalaire
    static void testScalarMultiplication() {
        Vector v(1.0f, 2.0f, 3.0f);
        Vector result = v * 2.0f;
        assertEqual(result.x, 2.0f, "testScalarMultiplication - x");
        assertEqual(result.y, 4.0f, "testScalarMultiplication - y");
        assertEqual(result.z, 6.0f, "testScalarMultiplication - z");
    }

    // Test du produit scalaire (dot product)
    static void testDotProduct() {
        Vector v1(1.0f, 2.0f, 3.0f);
        Vector v2(4.0f, 5.0f, 6.0f);
        float result = v1 * v2;
        assertEqual(result, 32.0f, "testDotProduct");
    }

    // Test du produit vectoriel (cross product)
    static void testCrossProduct() {
        Vector v1(1.0f, 0.0f, 0.0f);
        Vector v2(0.0f, 1.0f, 0.0f);
        Vector result = v1 ^ v2;
        assertEqual(result.x, 0.0f, "testCrossProduct - x");
        assertEqual(result.y, 0.0f, "testCrossProduct - y");
        assertEqual(result.z, 1.0f, "testCrossProduct - z");
    }

    // Test de la normalisation d'un vecteur
    static void testNormalize() {
        Vector v(3.0f, 4.0f, 0.0f);
        Vector result = v.normalize();
        assertEqual(result.x, 0.6f, "testNormalize - x");
        assertEqual(result.y, 0.8f, "testNormalize - y");
        assertEqual(result.z, 0.0f, "testNormalize - z");
    }

    // Lancer tous les tests
    static void runAllTests() {
        std::cout << "Running tests..." << std::endl;
        testConstructorWithTwoArgs();
        testAddition();
        testSubtraction();
        testScalarMultiplication();
        testDotProduct();
        testCrossProduct();
        testNormalize();
        std::cout << "Tests finished." << std::endl;
    }
};
