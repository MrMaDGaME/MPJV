#pragma once

#include "ofMain.h"
#include "ofxGui.h"

// Classes physiques et forces
#include "Force/Generators/InputForceGenerator.h"
#include "Force/ObjectForceRegistry.h"
#include "Force/Generators/GravityForceGenerator.h"

// Mathématiques
#include "maths/Matrix3x3.h"
#include "maths/Quaternion.h"

// Objets physiques
#include "Objects/Rigidbodies/Box.h"
#include "Objects/Rigidbodies/BoxTypes/UniformBox.h"
#include "Objects/Rigidbodies/BoxTypes/CoreBox.h"

class ofApp : public ofBaseApp {
public:
    // Méthodes principales
    void setup() override; // Initialisation
    void update() override; // Mise à jour
    void draw() override; // Dessin de la scène
    void keyPressed(int key) override; // Gestion des entrées clavier

private:
    // Méthodes auxiliaires
    void launchBox(); // Lancer une boîte avec une force initiale
    void createNewBox(); // Créer une nouvelle boîte
    void createNewCoreBox();
    void createNewUniformBox();

    // Caméra pour la visualisation 3D
    ofEasyCam cam;

    // Interface utilisateur (GUI)
    ofxPanel gui;
    ofxFloatSlider gravityScaleSlider; // Échelle de gravité
    ofxFloatSlider appliedForceXSlider; // Force appliquée (X)
    ofxFloatSlider appliedForceYSlider; // Force appliquée (Y)
    ofxFloatSlider appliedForceZSlider; // Force appliquée (Z)
    ofxFloatSlider forcePositionXSlider; // Centre de masse (X)
    ofxFloatSlider forcePositionYSlider; // Centre de masse (Y)
    ofxFloatSlider forcePositionZSlider; // Centre de masse (Z)

    // Gestion des objets physiques
    std::shared_ptr<RigidBody> current_rig; // Boîte actuellement active
    std::vector<std::shared_ptr<RigidBody>> rigidbodies; // Liste de toutes les boîtes créées

    // Générateurs de forces
    std::shared_ptr<GravityForceGenerator> gravity; // Générateur de gravité
    std::shared_ptr<ImpulseForceGenerator> impulseForce; // Générateur de force basé sur les sliders
    std::shared_ptr<Vector> impulseForceVector; // Vecteur directionnel pour la force d'entrée

    // Registre des forces
    std::shared_ptr<ObjectForceRegistry> forceRegistry; // Gestionnaire des forces appliquées aux objets
};
