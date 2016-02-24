#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
	
    controlMonitor.setup();
}


void ofApp::update() {
    controlMonitor.update();
}

void ofApp::draw() {
    controlMonitor.draw();
}

void ofApp::keyPressed(int key) {
//	if(key == 'r') {
//		tracker.reset();
//	}
}
