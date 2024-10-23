#include "ofApp.h"

std::vector<std::shared_ptr<IObject>> ofApp::objects_;

//--------------------------------------------------------------
void ofApp::setup() {
    blob = make_shared<Blob>(100.f, 700.f, 0.f, 10.f, 1.f, ofColor::orange, 5.f, 10.f, 100.f);
    objects_.push_back(blob);
    auto input_force = make_shared<InputForceGenerator>(moveInput, 100.f);
    particleForceRegistry->add(blob, input_force);
    auto friction = make_shared<FrictionForceGenerator>(10.f);
    particleForceRegistry->add(blob, friction);
    
    auto obstacleA =make_shared<Particle>(600.f, 700.f, 0.f, 100.f, 10.f, ofColor::blue, 100.f);
    auto obstacleB =make_shared<Particle>(100.f, 200.f, 0.f, 100.f, 10.f, ofColor::blue, 100.f);
    objects_.push_back(obstacleA);
    objects_.push_back(obstacleB);

    obstacleB->set_velocity(Vector(1,1,0));
    
    //auto obstacleC =make_shared<Particle>(1000.f, 700.f, 0.f, 50.f, 10.f, ofColor::white, 100.f);
    auto obstacleC =make_shared<Particle>(900.f, 700.f, 0.f, 50.f, true);
    auto obstacleD =make_shared<Particle>(1100.f, 700.f, 0.f, 50.f, true);
    objects_.push_back(obstacleC);
    objects_.push_back(obstacleD);
    
    auto obstacleE = make_shared<Particle>(900.f, 600.f, 0.f, 50.f, 10.f, ofColor::yellow, 100.f);
    auto obstacleF = make_shared<Particle>(1100.f, 400.f, 0.f, 50.f, 10.f, ofColor::yellow, 100.f);

    objects_.push_back(obstacleE);
    objects_.push_back(obstacleF);
    
    auto gravity = make_shared<GravityForceGenerator>();
    particleForceRegistry->add(obstacleE, gravity);
    particleForceRegistry->add(obstacleF, gravity);

    particleCollisionRegistry->AddCableCollision(obstacleA, obstacleB, 300);
    for (auto object = objects_.begin(); object != objects_.end(); ++object) {
        for (auto other = object; other != objects_.end(); ++other) {
            if (object != other) {
                object->get()->fill_object_collision(*other, particleCollisionRegistry, Inter, DEFAULT_BOUNCE);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    // Suppression des particules hors de l'écran
    auto del_it = std::remove_if(objects_.begin(),
                                 objects_.end(),
                                 [this](shared_ptr<IObject>& p) {
                                     if (p->get_position().y > static_cast<float>(ofGetHeight()) || p->get_position().x > static_cast<float>(
                                         ofGetWidth()) || p->get_position().z > 0 || p->get_position().x < 0 || p->get_position().y < 0) {
                                         particleForceRegistry->remove(p);
                                         return true;
                                     }
                                     return false;
                                 });
    objects_.erase(del_it, objects_.end());
    // Update particles
    particleForceRegistry->update_forces();
    particleCollisionRegistry->CheckCollision(0.0f);
    for (const auto& p : objects_) {
        p->update();
    }
    particleCollisionRegistry->CheckCollision(0.0f);
}

//--------------------------------------------------------------
void ofApp::draw() {
    // Dessiner les objets
    for (const auto& p : objects_) {
        p->draw();
    }

    // Affichage du framerate
    ofSetColor(ofColor::white);
    ofDrawBitmapString("rafraîchissement : " + ofToString(ofGetFrameRate()) + " fps", 10, 10);

    // Afficher le nombre de particules attachées au Blob
    ofSetColor(ofColor::orange);
    ofDrawBitmapString("Compteur de particules : " + ofToString(int(blob->get_particle_count())), 10, 30);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
    case OF_KEY_LEFT:
        moveInput->x = -1;
        break;
    case OF_KEY_RIGHT:
        moveInput->x = 1;
        break;
    case OF_KEY_UP:
        moveInput->y = -1;
        break;
    case OF_KEY_DOWN:
        moveInput->y = 1;
        break;
    case ' ':
        blob->add_new_blob();
        break;
    case 's':
        blob->divide();
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
    case OF_KEY_LEFT:
    case OF_KEY_RIGHT:
        moveInput->x = 0;
        break;
    case OF_KEY_UP:
    case OF_KEY_DOWN:
        moveInput->y = 0;
        break;
    default:
        break;
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

void ofApp::add_object(shared_ptr<IObject> object)
{
    objects_.push_back(object);
}

void ofApp::remove_object(shared_ptr<IObject> object)
{
    objects_.erase(std::remove(objects_.begin(), objects_.end(), object), objects_.end());
}


void ofApp::spawnBullet(float angle, float speed) {
    const auto p = make_shared<Bullet>(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->set_velocity(initialVelocity);
    objects_.push_back(p);
    particleForceRegistry->add(p, gravity);
}

void ofApp::spawnLaser(float angle, float speed) {
    const auto p = make_shared<Laser>(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->set_velocity(initialVelocity);
    objects_.push_back(p);
    particleForceRegistry->add(p, gravity);
}

void ofApp::spawnCanonBall(float angle, float speed) {
    const auto p = make_shared<CanonBall>(100.f, 700.f, 0.f);
    Vector initialVelocity(speed * cos(angle), speed * sin(angle), 0.f);
    p->set_velocity(initialVelocity);
    objects_.push_back(p);
    particleForceRegistry->add(p, gravity);
}
