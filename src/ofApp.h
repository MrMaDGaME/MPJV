#pragma once
#include <complex>
#include <iostream>
#include <numeric>
#include <string_view>
#include <vector>
#include "ofMain.h"
#include "ofxGui.h"
#include "Objects/Projectiles/Bullet.h"
#include "Objects/Projectiles/Laser.h"
#include "Objects/Projectiles/CanonBall.h"
#include "Objects/Particle.h"
#include "Collision/ParticleCollisionRegistry.h"
#include "Force/ObjectForceRegistry.h"
#include "Force/Generators/GravityForceGenerator.h"
#include "Force/Generators/InputForceGenerator.h"
#include "Force/Generators/FrictionForceGenerator.h"
#include "Objects/Blob.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    void spawnBullet(float angle, float speed);
    void spawnLaser(float angle, float speed);
    void spawnCanonBall(float angle, float speed);
    // Méthodes de rappel pour les boutons
    void onBulletButtonPressed();
    void onLaserButtonPressed();
    void onCanonBallButtonPressed();

    ofxPanel gui;
    ofxButton laserbutton;
    ofxButton bulletbutton;
    ofxButton canonballbutton;
    ofxFloatSlider angleSlider;
    ofxFloatSlider speedSlider;
    ObjectForceRegistry particleForceRegistry;
    ParticleCollisionRegistry particleCollisionRegistry = ParticleCollisionRegistry(&particleForceRegistry);
    shared_ptr<IParticleForceGenerator> gravity = make_shared<GravityForceGenerator>(9.81f);
    shared_ptr<Vector> moveInput = make_shared<Vector>(0.f, 0.f, 0.f);
    std::vector<shared_ptr<IObject>> objects_;
    shared_ptr<Blob> blob = nullptr;
};
