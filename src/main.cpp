#include "ofMain.h"
#include "ofApp.h"
#include "tests/VectorTests.h"
#include "tests/QuaternionTest.h"

//========================================================================
int main() {
    VectorTest::runAllTests();
    QuaternionTest::runAllTests();
    //Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    ofGLWindowSettings settings;
    settings.setSize(1800, 1000);
    settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
    auto window = ofCreateWindow(settings);
    ofRunApp(window, make_shared<ofApp>());
    ofRunMainLoop();
}
