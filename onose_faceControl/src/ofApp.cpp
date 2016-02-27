#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    midiControl.setup();
    faceTracker.setup();
    controlMonitor.setup();
}


void ofApp::update() {
    midiControl.update();
    faceTracker.update();
    controlMonitor.update();
    
    midiControl.faceOriControl(faceTracker);
}

void ofApp::draw() {
    controlMonitor.draw(faceTracker);
    midiControl.viewIndicator();
}

void ofApp::keyPressed(int key) {
    
    switch (key) {
        case ' ':
//            midiControl.controlWave(16, 0.01);
            break;
        case 'r':
            break;
        default:
            break;
    }
}
void ofApp::mouseDragged(int x, int y, int button){
    midiControl.mouseDragged(x, y, button);
}

void ofApp::exit(){
    midiControl.exit();
}