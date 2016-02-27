//
//  ControlMonitor.cpp
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#include "ControlMonitor.h"

ControlMonitor::ControlMonitor(){
    
}

void ControlMonitor::setup(){
}

void ControlMonitor::update(){
    
}

void ControlMonitor::draw(FaceTracker& faceTracker){
    ofSetColor(255);
    faceTracker.drawCam();
    ofDrawBitmapString("FPS: " + ofToString((int) ofGetFrameRate()), 10, 20);
//    faceTracker.drawTracker();
    
    // easyCam.begin();
    ofSetupScreenOrtho(conf.camWidth, conf.camHeight, -1000, 1000);
    ofTranslate(conf.camWidth / 2, conf.camHeight / 2);
    
    ofPushMatrix();
    applyMatrix(faceTracker.rotationMatrix);
    ofScale(5,5,5);
    drawControlCircle(faceTracker);
    ofPopMatrix();
    // easyCam.end();
}

void ControlMonitor::drawControlCircle(FaceTracker& faceTracker){
    ofNoFill();
    if(faceTracker.getFound()){
        ofSetColor(255, 0, 0);
    }
    ofCircle(0, 0, 0, 30);
//    if(faceTracker.getMouseOpend()){
//        centerSphere.set(10, 10);
//        centerSphere.drawWireframe();
//    }
    ofFill();
    ofRect(30, -6, (faceTracker.orientation.x * 50), 4);
    ofRect(30, -2, (faceTracker.orientation.y * 50), 4);
    ofRect(30,  2, (faceTracker.orientation.z * 50), 4);
    ofDrawBitmapString("x: " + ofToString(faceTracker.orientation.x), 20, 20);
    ofDrawBitmapString("y: " + ofToString(faceTracker.orientation.y), 20, 26);
    ofDrawBitmapString("z: " + ofToString(faceTracker.orientation.z), 20, 32);
    ofDrawBitmapString("MH: " + ofToString(faceTracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT)), 20, 38);
    
}


