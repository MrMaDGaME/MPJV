#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Initialisation de l'interface utilisateur
    parametersGui.setup("Parameters", "forceSettings.xml", 10, 75);
    parametersGui.add(gravityScaleSlider.setup("Gravity Scale", 0.f, 0.f, 2.0f));
    parametersGui.add(appliedForceXSlider.setup("Applied Force X", 50.f, -50.f, 50.f));
    parametersGui.add(appliedForceYSlider.setup("Applied Force Y", 0.f, -50.f, 50.f));
    parametersGui.add(appliedForceZSlider.setup("Applied Force Z", 0.f, -50.f, 50.f));
    parametersGui.add(forcePositionXSlider.setup("Force position X", 0.f, -25.f, 25.f));
    parametersGui.add(forcePositionYSlider.setup("Force position Y", 0.f, -25.f, 25.f));
    parametersGui.add(forcePositionZSlider.setup("Force position Z", 0.f, -25.f, 25.f));

    drawGui.setup("Draw Settings", "drawSettings.xml", 10, 250);
    drawGui.add(drawForceToggle.setup("Draw Force Applied", true));
    drawGui.add(drawOctreeToggle.setup("Draw Octree", true));
    drawGui.add(drawBoundingSpheresToggle.setup("Draw Bounding Spheres", false));

    // Initialisation de la gravité
    gravity = std::make_shared<GravityForceGenerator>(gravityScaleSlider * -9.81f);

    // Initialisation du registre des forces
    forceRegistry = std::make_shared<ObjectForceRegistry>();
    collisionRegistry = std::make_shared<RigidbodyCollisionRegistry>(forceRegistry);

    // rigidbodies.push_back(std::make_shared<Plane>(Vector(0, 0, 100), 1000, 1000, ofColor::blue));

    // Configuration de la caméra
    cam.setDistance(500); // Distance de vue initiale

    tree = std::make_shared<ocTree>(Vector(), 10000.f);
}

//--------------------------------------------------------------
void ofApp::update() {
    tree->clear();
    collisionRegistry->clear();
    
    for (const auto& rigidbody : rigidbodies) {
        tree->insert(rigidbody);
    }
    for (const auto& pair : tree->getAllPairs()) {
        collisionRegistry->AddInterCollision(pair.first, pair.second, 0.5f);
    }

    collisionRegistry->computeInterCollisions();

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
        rigidbody->draw();
        if (drawBoundingSpheresToggle) {
            ofEnableAlphaBlending();
            ofSetColor(200, 100, 0, 127);
            auto boundingSphere = rigidbody->get_bounding_sphere();
            auto boundingSpherePosition = boundingSphere.getCenter();
            ofDrawSphere(boundingSpherePosition.x, boundingSpherePosition.y, boundingSpherePosition.z, boundingSphere.getRadius());
            ofDisableAlphaBlending();
        }
    }

    if (drawForceToggle && current_rig) {
        Vector forcePosition = current_rig->get_position() + Vector(forcePositionXSlider, forcePositionYSlider, forcePositionZSlider);
        ofSetColor(ofColor::red);
        ofDrawSphere(forcePosition.x, forcePosition.y, forcePosition.z, 5.f);
        ofSetColor(ofColor::yellow);
        ofDrawArrow(glm::vec3(forcePosition.x - appliedForceXSlider, forcePosition.y - appliedForceYSlider, forcePosition.z - appliedForceZSlider),
                    glm::vec3(forcePosition.x, forcePosition.y, forcePosition.z),
                    5.f);
    }

    if (drawOctreeToggle) {
        tree->draw();
    }

    cam.end();
    ofDisableDepthTest();

    // Dessiner l'interface utilisateur
    parametersGui.draw();
    drawGui.draw();

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
