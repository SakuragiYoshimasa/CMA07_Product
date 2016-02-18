#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetColor(255, 255, 255);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    ofSetLineWidth(0.5);
    mouseX = ofGetWidth()/2;
    mouseY = ofGetHeight()/2;
    
    for (int i = 0; i<NUM; i++) {
        rainX[i] = ofRandom(5.0,ofGetWidth()-5.0);
        rainY1[i] = ofRandom(-ofGetWidth(),-100.0);
        rainY2[i] = rainY1[i] + ofRandom(10.0, 100.0);
        speed_y[i] = 10;//= ofRandom(10.0, 30.0);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    for (int i = 0; i<NUM; i++) {
        
        rainY1[i] = rainY1[i] + speed_y[i];
        rainY2[i] = rainY2[i] + speed_y[i];
        
        // triangleY[i] = (mouseY / mouseX) * rainX[i];
        
        
        
        if (rainY1[i] > ofGetHeight()) {
            rainY1[i] = -100.0;
            rainY2[i] = rainY1[i] + ofRandom(10.0, 100.0);
        }
        
        if (rainX[i] > ofGetWidth()/2 && rainX[i] < ofGetWidth()/2 +300) {
            if ((rainY2[i] = rainX[i] * mouseY / mouseX)){
                
                rainY1[i] = -100.0;
                rainY2[i] = rainY1[i] + ofRandom(10.0, 100.0);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    for (int i = 0; i<NUM; i++) {
        ofLine(rainX[i], rainY1[i], rainX[i], rainY2[i]);
    }
    
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    
    triangleX =  sqrt(300*300-mouseY*mouseY);
    ofLine(0,0, triangleX, mouseY);
    
    
    
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
