#include "ofApp.h"
#include "Particle.h"

std::vector<Particle> particles;

//--------------------------------------------------------------
void ofApp::setup(){
	Particle p(0.f, 700.f, -100.f, 50.f, 1.f);
	particles.push_back(p);
	// p.applyForce(0.f, -1000.f, 0.f);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& p : particles) {
		// p.update();
		p.position += Vector(1.f, -1.f, 0.f);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (auto& p : particles) {
		p.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
