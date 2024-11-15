#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Objects/Rigidbodies/Box.h"
#include "Force/ObjectForceRegistry.h"
#include "Force/Generators/GravityForceGenerator.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    void launchBox();
    void createNewBox();

    ofEasyCam cam; // Caméra 3D
    shared_ptr<Box> box;
    vector<shared_ptr<Box>> boxes;
    shared_ptr<ObjectForceRegistry> forceRegistry = make_shared<ObjectForceRegistry>();
    shared_ptr<GravityForceGenerator> gravity;

    // Interface graphique
    ofxPanel gui;
    ofxFloatSlider launchAngleSlider;
    ofxFloatSlider azimuthAngleSlider;
    ofxFloatSlider initialSpeedSlider;
    ofxFloatSlider gravityScaleSlider;
    ofxFloatSlider appliedForceXSlider;
    ofxFloatSlider appliedForceYSlider;
    ofxFloatSlider appliedForceZSlider;
    ofxFloatSlider forceApplicationOffsetXSlider;
    ofxFloatSlider forceApplicationOffsetYSlider;
    ofxFloatSlider forceApplicationOffsetZSlider;
    ofxFloatSlider centerOfMassXSlider;
    ofxFloatSlider centerOfMassYSlider;
    ofxFloatSlider centerOfMassZSlider;
};
