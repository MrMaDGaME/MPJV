#include "ofApp.h"
#include "Particle.h"

std::vector<Particle> particles;

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

    gui.add(angleSlider.setup("Angle", 5,4.7,7.0)); // Angle en degrés, plage ajustée (0 à 90)
    gui.add(speedSlider.setup("Speed", 10, 0, 50)); // Vitesse ajustée (plage de 10 à 300)
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto& p : particles) {
        p.applyForce(0.f, 9.81f * p.mass, 0.f, 0.f); // Ajustez si nécessaire
        p.update();
    }
    ofRemove(particles, [](Particle& p) { return p.position.y > ofGetHeight() || p.position.x > ofGetWidth() || p.position.z > 0; });
}

//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();
    for (auto& p : particles) {
        p.draw();
    }

    ofSetColor(ofColor::black);
    ofDrawBitmapString("rafraîchissement : " + ofToString(ofGetFrameRate()) + " fps", 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
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
    Bullet p(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p.velocity = initialVelocity;
    p.applyForce(0.f, -9.81f * 0.1f, 0.f, 0.1f); // Ajustez la force appliquée pour simuler la résistance de l'air et la gravité
    particles.push_back(p);
}

void ofApp::spawnLaser(float angle, float speed) {
    Laser p(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p.velocity = initialVelocity;
    p.applyForce(0.f, -9.81f * 0.1f, 0.f, 0.1f); // Ajustez la force appliquée pour simuler la résistance de l'air et la gravité
    particles.push_back(p);
}

void ofApp::spawnCanonBall(float angle, float speed) {
    CanonBall p(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p.velocity = initialVelocity;
    p.applyForce(0.f, -9.81f * 0.1f, 0.f, 0.1f); // Ajustez la force appliquée pour simuler la résistance de l'air et la gravité
    particles.push_back(p);
}
