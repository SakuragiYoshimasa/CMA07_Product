#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 100);
    ofSetFrameRate(30);
    ofSetCircleResolution(64);
    
    soundplayer.loadSound("2-05 Superstition.mp3");
    soundplayer.setLoop(false);
    soundplayer.setVolume(1.0);
    soundplayer.play();
    
    
    volume = ofSoundGetSpectrum(1);
    if (volume[0]*1000 > 100) {
        
        Bounce b;
        bounce.push_back(b);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    for(int i=0; i < bounce.size(); i++){
        bounce[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0; i < bounce.size(); i++){
        bounce[i].draw();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
