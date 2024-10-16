#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    // Initialisation des boutons
    laserbutton.addListener(this, &ofApp::onLaserButtonPressed);
    bulletbutton.addListener(this, &ofApp::onBulletButtonPressed);
    canonballbutton.addListener(this, &ofApp::onCanonBallButtonPressed);

    gui.setup();
    gui.add(laserbutton.setup("Laser"));
    gui.add(bulletbutton.setup("Bullet"));
    gui.add(canonballbutton.setup("CanonBall"));

    gui.add(angleSlider.setup("Angle", 5,4.7,7.0)); // Angle en degrés
    gui.add(speedSlider.setup("Speed", 10, 0, 12)); // Vitesse ajustée
    
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto* p : particles) {
        if (p->position.y > ofGetHeight() || p->position.x > ofGetWidth() || p->position.z > 0){
            particleForceRegistry.Remove(p);
            delete p;
        }
//        p.applyForce(0.f, p.inv_mass != 0 ? 9.81f / p.inv_mass : 0, 0.f, 0.f); // Ajustez si nécessaire
        p->update();
    }
    //particleForceRegistry.UpdateForces(1.f / 60.f);
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();
    for (auto* p : particles) {
        p->draw();
    }

    ofSetColor(ofColor::white);
    ofDrawBitmapString("rafraîchissement : " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
    case OF_KEY_LEFT:
        moveInput.x = -1;
        break;
    case OF_KEY_RIGHT:
        moveInput.x = 1;
        break;
    case OF_KEY_UP:
        moveInput.y = -1;
        break;
    case OF_KEY_DOWN:
        moveInput.y = 1;
        break;
    default: break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
    case OF_KEY_LEFT:
    case OF_KEY_RIGHT:
        moveInput.x = 0;
        break;
    case OF_KEY_UP:
    case OF_KEY_DOWN:
        moveInput.y = 0;
        break;
    default: break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

// Méthodes de rappel modifiées pour les boutons
void ofApp::onBulletButtonPressed() {
    float angle = angleSlider;
    float speed = speedSlider; // Vitesse sans réduction
    spawnBullet(angle, speed);
}

void ofApp::onLaserButtonPressed() {
    float angle = angleSlider;
    float speed = speedSlider; // Vitesse sans réduction
    spawnLaser(angle, speed);
}

void ofApp::onCanonBallButtonPressed() {
    float angle = angleSlider;
    float speed = speedSlider; // Vitesse sans réduction
    spawnCanonBall(angle, speed);
}

void ofApp::spawnBullet(float angle, float speed) {
    Bullet *p = new Bullet(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->velocity = initialVelocity;
    particles.push_back(p);
    particleForceRegistry.Add(p, gravity);
}

void ofApp::spawnLaser(float angle, float speed) {
    Laser *p = new Laser(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->velocity = initialVelocity;
    particles.push_back(p);
    particleForceRegistry.Add(p, gravity);
}

void ofApp::spawnCanonBall(float angle, float speed) {
    CanonBall *p = new CanonBall(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->velocity = initialVelocity;
    particles.push_back(p);
    particleForceRegistry.Add(p, gravity);
}
