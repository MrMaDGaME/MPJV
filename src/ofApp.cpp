#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(launchAngleSlider.setup("Launch Angle (degrees)", 45.f, 0.f, 90.f));
    gui.add(azimuthAngleSlider.setup("Azimuth Angle (degrees)", 0.f, -180.f, 180.f));
    gui.add(initialSpeedSlider.setup("Initial Speed", 2.f, 0.f, 10.f));
    gui.add(gravityScaleSlider.setup("Gravity Scale", 0.3f, 0.1f, 2.0f));
    gui.add(appliedForceXSlider.setup("Applied Force X", 10.f, -50.f, 50.f));
    gui.add(appliedForceYSlider.setup("Applied Force Y", 5.f, -50.f, 50.f));
    gui.add(appliedForceZSlider.setup("Applied Force Z", 0.f, -50.f, 50.f));
    gui.add(centerOfMassXSlider.setup("Center of Mass X", 0.f, -25.f, 25.f));
    gui.add(centerOfMassYSlider.setup("Center of Mass Y", 0.f, -25.f, 25.f));
    gui.add(centerOfMassZSlider.setup("Center of Mass Z", 0.f, -25.f, 25.f));

    gravity = make_shared<GravityForceGenerator>(-9.81f * gravityScaleSlider);

    createNewBox();
    cam.setDistance(500); // Positionner la caméra pour voir la scène
}

//--------------------------------------------------------------
void ofApp::update() {
    gravity->setGravity(-9.81f * gravityScaleSlider);

    for (auto& box : boxes) {
        forceRegistry->update_forces();
        box->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest(); // Activer le test de profondeur pour le rendu 3D
    cam.begin();

    for (const auto& box : boxes) {
        ofSetColor(ofColor::blue);
        box->draw();

        // Dessiner le centre de masse comme une sphère rouge
        ofSetColor(ofColor::red);
        ofDrawSphere(box->get_position().x + centerOfMassXSlider,
            box->get_position().y + centerOfMassYSlider,
            box->get_position().z + centerOfMassZSlider, 5.f);
    }

    cam.end(); // Fin de la scène 3D
    ofDisableDepthTest(); // Désactiver le test de profondeur pour la GUI
    gui.draw();

    // Instructions
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
    ofDrawBitmapString("Press 'l' to launch the box, 'n' to spawn a new box", 10, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'l') {
        launchBox();
    }
    else if (key == 'n') {
        createNewBox();
    }
}

//--------------------------------------------------------------
void ofApp::launchBox() {
    if (box) {
        // Convertir l'angle de lancement et l'azimut en radians
        float launchAngleRad = ofDegToRad(launchAngleSlider);
        float azimuthAngleRad = ofDegToRad(azimuthAngleSlider);

        // Calculer les composantes de la vélocité initiale avec l'azimut et l'angle de lancement
        float vx = initialSpeedSlider * cos(launchAngleRad) * cos(azimuthAngleRad);
        float vy = initialSpeedSlider * sin(launchAngleRad);
        float vz = initialSpeedSlider * cos(launchAngleRad) * sin(azimuthAngleRad);

        Vector initialVelocity(vx, vy, vz);
        box->set_velocity(initialVelocity);

        // Définir le centre de masse en utilisant les sliders
        Vector newCenterOfMass(centerOfMassXSlider, centerOfMassYSlider, centerOfMassZSlider);
        box->setCenterOfMass(newCenterOfMass);

        // Appliquer la force directement au centre de masse
        Vector appliedForce(appliedForceXSlider, appliedForceYSlider, appliedForceZSlider);
        box->addForce(newCenterOfMass, appliedForce);  // La force est appliquée au centre de masse ajusté
    }
}

//--------------------------------------------------------------
void ofApp::createNewBox() {
    // Initialiser une nouvelle boîte au centre avec des dimensions et masse définies
    box = make_shared<Box>(0.f, 0.f, 0.f, 50.f, 50.f, 50.f, 10.f, Matrix3x3::identity());
    boxes.push_back(box);
    forceRegistry->add(box, gravity);
}
