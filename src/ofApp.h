#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Objects/Rigidbodies/Box.h"
#include "Force/ObjectForceRegistry.h"
#include "Force/Generators/GravityForceGenerator.h"
#include "Objects/Rigidbodies/RigidBody.h"
#include "maths/Quaternion.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    void launchBox();      // Lancer une boîte avec une force initiale
    void createNewBox();    // Créer une nouvelle boîte

    ofEasyCam cam;          // Caméra 3D
    shared_ptr<Box> box;
    vector<shared_ptr<Box>> boxes;
    shared_ptr<ObjectForceRegistry> forceRegistry = make_shared<ObjectForceRegistry>();
    shared_ptr<GravityForceGenerator> gravity;

    // Interface graphique
    ofxPanel gui;
    ofxFloatSlider launchAngleSlider;           // Angle de lancement
    ofxFloatSlider azimuthAngleSlider;          // Angle d'azimut
    ofxFloatSlider initialSpeedSlider;          // Vitesse initiale
    ofxFloatSlider gravityScaleSlider;          // Gravité
    ofxFloatSlider appliedForceXSlider;         // Force appliquée en X
    ofxFloatSlider appliedForceYSlider;         // Force appliquée en Y
    ofxFloatSlider appliedForceZSlider;         // Force appliquée en Z
    ofxFloatSlider centerOfMassXSlider;         // Centre de masse X
    ofxFloatSlider centerOfMassYSlider;         // Centre de masse Y
    ofxFloatSlider centerOfMassZSlider;         // Centre de masse Z
    ofLight directionalLight;
};

