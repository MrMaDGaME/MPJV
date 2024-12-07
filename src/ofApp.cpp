#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Initialisation de l'interface utilisateur
    gui.setup();
    gui.add(gravityScaleSlider.setup("Gravity Scale", 0.f, 0.f, 2.0f));
    gui.add(appliedForceXSlider.setup("Applied Force X", 50.f, -50.f, 50.f));
    gui.add(appliedForceYSlider.setup("Applied Force Y", 0.f, -50.f, 50.f));
    gui.add(appliedForceZSlider.setup("Applied Force Z", 0.f, -50.f, 50.f));
    gui.add(forcePositionXSlider.setup("Force position X", 0.f, -25.f, 25.f));
    gui.add(forcePositionYSlider.setup("Force position Y", 0.f, -25.f, 25.f));
    gui.add(forcePositionZSlider.setup("Force position Z", 0.f, -25.f, 25.f));

    // Initialisation de la gravité
    gravity = std::make_shared<GravityForceGenerator>(-9.81f * gravityScaleSlider);

    // Initialisation du registre des forces
    forceRegistry = std::make_shared<ObjectForceRegistry>();

    // Configuration de la caméra
    cam.setDistance(500); // Distance de vue initiale

    auto plane = std::make_shared<Plane>(Vector(), 100.f, 100.f, Vector(0, 1, 0), ofColor::green);
}

//--------------------------------------------------------------
void ofApp::update() {
    // Mettre à jour la gravité en fonction des sliders
    gravity->setGravity(-9.81f * gravityScaleSlider);

    // Mettre à jour la direction de la force d'entrée
    impulseForceVector = std::make_shared<Vector>(appliedForceXSlider, appliedForceYSlider, appliedForceZSlider);
    impulseForce = std::make_shared<ImpulseForceGenerator>(*impulseForceVector);

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
    for (const auto& rigidbody : rigidbodies) {
        rigidbody->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableDepthTest();
    cam.begin();

    // Dessiner toutes les boîtes
    for (const auto& rigidbody : rigidbodies) {
        ofSetColor(ofColor::blue);
        rigidbody->draw();

        // Dessiner le centre de masse en rouge
        if (rigidbody->get_inv_mass() > 0) { // Ne pas dessiner le centre de masse pour les objets statiques
            Vector cmPosition = rigidbody->get_position() + Vector(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider);
            ofSetColor(ofColor::red);
            ofDrawSphere(cmPosition.x, cmPosition.y, cmPosition.z, 5.f);
            ofSetColor(ofColor::yellow);
            ofDrawArrow(glm::vec3(cmPosition.x - appliedForceXSlider, cmPosition.y - appliedForceYSlider, cmPosition.z - appliedForceZSlider),
                        glm::vec3(cmPosition.x, cmPosition.y, cmPosition.z),
                        5.f);
        }
    }

    cam.end();
    ofDisableDepthTest();

    // Dessiner l'interface utilisateur
    gui.draw();

    // Afficher des informations de débogage
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Frame Rate: " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
    ofDrawBitmapString("Number of Boxes: " + ofToString(rigidbodies.size()), 10, 30);
    ofDrawBitmapString("Press 'l' to launch the box, 'n' to spawn a new box", 10, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'l') {
        launchBox(); // Lancer la boîte avec une force initiale
    }
    else if (key == 'n') {
        createNewCoreBox(); // Créer une nouvelle boîte
    }
    else if (key == 'b') {
        createNewUniformBox();
    }
}

//--------------------------------------------------------------
void ofApp::launchBox() {
    if (current_rig) {
        forceRegistry->add(current_rig, impulseForce, Vector(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider));
    }
}

//--------------------------------------------------------------
void ofApp::createNewBox() {
    // Initialiser une nouvelle boîte
    current_rig = std::make_shared<Box>(0.f, 0.f, 0.f, 50.f, 50.f, 50.f, 10.f, Matrix3x3::identity());
    rigidbodies.push_back(current_rig);

    // Ajouter la boîte au registre des forces avec la gravité
    forceRegistry->add(current_rig, gravity);
}

void ofApp::createNewCoreBox() {
    current_rig = std::make_shared<CoreBox>(0.f, 0.f, 0.f);
    rigidbodies.push_back(current_rig);

    // Ajouter la boîte au registre des forces avec la gravité
    forceRegistry->add(current_rig, gravity);
}

void ofApp::createNewUniformBox() {
    current_rig = std::make_shared<UniformBox>(0.f, 0.f, 0.f);
    rigidbodies.push_back(current_rig);

    // Ajouter la boîte au registre des forces avec la gravité
    forceRegistry->add(current_rig, gravity);
}
