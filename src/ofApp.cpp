#include "ofApp.h"
#include "Particle.h"
#include <typeinfo>

std::vector<Particle> particles;

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(laserbutton.setup("laser"));
    gui.add(bulletbutton.setup("bullet"));
    gui.add(canonballbutton.setup("canonball"));
}

//--------------------------------------------------------------
void ofApp::update() {
    for (auto& p : particles) {
        p.applyForce(0.f, 10.f * p.mass, 0.f, 0.f);
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
    ofDrawBitmapString("rafraîchissement : "+ ofToString(ofGetFrameRate()) + " fps" , 10, 10);}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        Bullet p(100.f, 700.f, -10.f);
        p.applyForce(1000.f, -1000.f, 0.f, 0.1f);
        particles.push_back(p);
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
