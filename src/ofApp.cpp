#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(launchAngleSlider.setup("Launch Angle (degrees)", 45.f, 0.f, 90.f));
    gui.add(azimuthAngleSlider.setup("Azimuth Angle (degrees)", 0.f, -180.f, 180.f));
    gui.add(initialSpeedSlider.setup("Initial Speed", 10.f, 0.f, 100.f));
    gui.add(gravityScaleSlider.setup("Gravity Scale", 0.3f, 0.1f, 2.0f));
    gui.add(appliedForceXSlider.setup("Applied Force X", 10.f, -50.f, 50.f));
    gui.add(appliedForceYSlider.setup("Applied Force Y", 5.f, -50.f, 50.f));
    gui.add(appliedForceZSlider.setup("Applied Force Z", 0.f, -50.f, 50.f));
    gui.add(centerOfMassXSlider.setup("Center of Mass X", 0.f, -25.f, 25.f));
    gui.add(centerOfMassYSlider.setup("Center of Mass Y", 0.f, -25.f, 25.f));
    gui.add(centerOfMassZSlider.setup("Center of Mass Z", 0.f, -25.f, 25.f));

    // Initialisation de la gravité
    gravity = make_shared<GravityForceGenerator>(-9.81f * gravityScaleSlider);

    createNewBox();
    cam.setDistance(500);  // Positionner la caméra pour voir la scène
}

//--------------------------------------------------------------
void ofApp::update() {
    // Mettre à jour l'intensité de la gravité en fonction du slider
    gravity->setGravity(-9.81f * gravityScaleSlider);

    // Déclare newCenterOfMass en dehors du bloc conditionnel
    Vector newCenterOfMass(centerOfMassXSlider, centerOfMassYSlider, centerOfMassZSlider);

    // Mettre à jour le centre de masse de la boîte active en fonction des sliders
    if (box) {
        box->setCenterOfMass(newCenterOfMass);  // Met à jour le centre de masse
    }

    // Applique la force des sliders et met à jour chaque boîte
    Vector appliedForce(appliedForceXSlider, appliedForceYSlider, appliedForceZSlider);

    for (auto& box : boxes) {
        forceRegistry->update_forces();  // Applique les forces enregistrées, comme la gravité

        // Appliquer la force au point d'application (centre de masse mis à jour)
        box->addForce(appliedForce, newCenterOfMass);

        box->update();  // Passe deltaTime pour une intégration correcte
    }
}





//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest();
    cam.begin();

    // Dessiner chaque boîte
    for (const auto& box : boxes) {
        ofSetColor(ofColor::blue);
        box->draw();

        // Afficher le centre de masse sous forme de sphère rouge semi-transparente
        Vector cmPosition = box->get_position() + Vector(centerOfMassXSlider, centerOfMassYSlider, centerOfMassZSlider);
        ofSetColor(255, 0, 0, 128); // Couleur rouge avec transparence (128 sur 255)
        ofDrawSphere(cmPosition.x, cmPosition.y, cmPosition.z, 5.f); // Rayon de 5 pour la visibilité
    }

    cam.end();
    ofDisableDepthTest();
    gui.draw();

    ofSetColor(ofColor::white);
    ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
    ofDrawBitmapString("Press 'l' to launch the box, 'n' to spawn a new box", 10, 30);
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
        // Calcul de la vélocité initiale selon l'angle de lancement et l'azimut
        float launchAngleRad = ofDegToRad(launchAngleSlider);
        float azimuthAngleRad = ofDegToRad(azimuthAngleSlider);
        float vx = initialSpeedSlider * cos(launchAngleRad) * cos(azimuthAngleRad);
        float vy = initialSpeedSlider * sin(launchAngleRad);
        float vz = initialSpeedSlider * cos(launchAngleRad) * sin(azimuthAngleRad);
        Vector initialVelocity(vx, vy, vz);
        box->set_velocity(initialVelocity);

        // Appliquer une force initiale basée sur les sliders
        Vector appliedForce(appliedForceXSlider, appliedForceYSlider, appliedForceZSlider);
        box->addForce(appliedForce);  // Appliquer la force au centre de masse
    }
}

//--------------------------------------------------------------
void ofApp::createNewBox() {
    // Initialiser une nouvelle boîte avec les valeurs par défaut
    box = make_shared<Box>(0.f, 0.f, 0.f, 50.f, 50.f, 50.f, 10.f, Matrix3x3::identity());
    boxes.push_back(box);
    forceRegistry->add(box, gravity);
}
