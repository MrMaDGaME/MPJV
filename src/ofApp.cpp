#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Initialisation de l'interface utilisateur
    gui.setup();
    gui.add(launchAngleSlider.setup("Launch Angle (degrees)", 45.f, 0.f, 90.f));
    gui.add(azimuthAngleSlider.setup("Azimuth Angle (degrees)", 0.f, -180.f, 180.f));
    gui.add(initialSpeedSlider.setup("Initial Speed", 10.f, 0.f, 100.f));
    gui.add(gravityScaleSlider.setup("Gravity Scale", 0.3f, 0.1f, 2.0f));
    gui.add(appliedForceXSlider.setup("Applied Force X", 10.f, -50.f, 50.f));
    gui.add(appliedForceYSlider.setup("Applied Force Y", 5.f, -50.f, 50.f));
    gui.add(appliedForceZSlider.setup("Applied Force Z", 0.f, -50.f, 50.f));
    gui.add(forcePositionXSlider.setup("Force position X", 0.f, -25.f, 25.f));
    gui.add(forcePositionYSlider.setup("Force position Y", 0.f, -25.f, 25.f));
    gui.add(forcePositionZSlider.setup("Force position Z", 0.f, -25.f, 25.f));

    // Initialisation de la gravité
    gravity = std::make_shared<GravityForceGenerator>(-9.81f * gravityScaleSlider);

    // Initialisation du registre des forces
    forceRegistry = std::make_shared<ObjectForceRegistry>();

    // Création d'une première boîte
    createNewBox();

    // Configuration de la caméra
    cam.setDistance(500);  // Distance de vue initiale
}

//--------------------------------------------------------------
void ofApp::update() {
    // Mettre à jour la gravité en fonction des sliders
    gravity->setGravity(-9.81f * gravityScaleSlider * 0);

    // Mettre à jour la direction de la force d'entrée
    inputForceVector = std::make_shared<Vector>(appliedForceXSlider, appliedForceYSlider, appliedForceZSlider);
    impulseForce = std::make_shared<ImpulseForceGenerator>(*inputForceVector);

    /*
    // Mettre à jour le centre de masse de la boîte active
    if (box) {
        Vector newCenterOfMass(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider);
        box->setCenterOfMass(newCenterOfMass);
    }
    */

    // Appliquer les forces enregistrées
    forceRegistry->update_forces();

    // Mettre à jour chaque boîte
    for (auto& box : boxes) {
        box->update();
    }

    forcePosition = Vector(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest();
    cam.begin();

    // Dessiner toutes les boîtes
    for (const auto& box : boxes) {
        ofSetColor(ofColor::blue);
        box->draw();

        // Dessiner le centre de masse en rouge
        Vector cmPosition = box->get_position() + Vector(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider);
        ofSetColor(ofColor::red);
        ofDrawSphere(cmPosition.x, cmPosition.y, cmPosition.z, 5.f);
    }

    cam.end();
    ofDisableDepthTest();

    // Dessiner un point a forcePosition
    ofSetColor(ofColor::red);
    ofDrawSphere(forcePosition.x, forcePosition.y, forcePosition.z, 5.f);
    

    // Dessiner l'interface utilisateur
    gui.draw();

    // Afficher des informations de débogage
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
    ofDrawBitmapString("Number of Boxes: " + ofToString(boxes.size()), 10, 30);
    ofDrawBitmapString("Press 'l' to launch the box, 'n' to spawn a new box", 10, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'l') {
        launchBox();  // Lancer la boîte avec une force initiale
    }
    else if (key == 'n') {
        createNewBox();  // Créer une nouvelle boîte
    }
}

//--------------------------------------------------------------
void ofApp::launchBox() {
    if (box) {
        forceRegistry->add(box, impulseForce, forcePosition);
    }
}

//--------------------------------------------------------------
void ofApp::createNewBox() {
    // Initialiser une nouvelle boîte
    box = std::make_shared<Box>(0.f, 0.f, 0.f, 50.f, 50.f, 50.f, 10.f, Matrix3x3::identity());
    boxes.push_back(box);

    // Ajouter la boîte au registre des forces avec la gravité
    forceRegistry->add(box, gravity);
}
