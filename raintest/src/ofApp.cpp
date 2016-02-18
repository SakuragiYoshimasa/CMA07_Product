#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetColor(255, 255, 255);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    ofSetLineWidth(0.5);
    
    for (int i = 0; i<=NUM; i++) {
        rainX[i] = ofRandom(5,ofGetWidth()-5);
        rainY1[i] = ofRandom(-ofGetWidth(),-100);
        rainY2[i] = rainY1[i] + ofRandom(10,100);
        speed_y[i] = ofRandom(10, 30);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i<=NUM; i++) {
        
        rainY1[i] = rainY1[i] + speed_y[i];
        rainY2[i] = rainY2[i] + speed_y[i];
        
        if (rainY1[i] > ofGetHeight()) {
            rainY1[i] = -100;
            rainY2[i] = rainY1[i] + ofRandom(10,100);
        }
        
        if (rainX[i] > 100 && rainX[i] <500) {
            if (rainY2[i] >ofGetHeight()/2-15 && rainY2[1]<ofGetHeight()/2+15) {
                rainY1[i] = -1000;
                rainY2[i] = rainY1[i] + ofRandom(10,100);
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    
    for (int i = 0; i<=NUM; i++) {
        ofLine(rainX[i], rainY1[i], rainX[i], rainY2[i]);
    }
    
    ofLine(100, ofGetHeight()/2, 500, ofGetHeight()/2);
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
