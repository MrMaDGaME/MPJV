#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Projectiles/Bullet.h"
#include "Projectiles/Laser.h"
#include "Projectiles/CanonBall.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

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
    ParticleForceRegistry particleForceRegistry;
    GravityForceGenerator gravity = GravityForceGenerator(9.81f);
    
    std::vector<Particle *> particles;
};
