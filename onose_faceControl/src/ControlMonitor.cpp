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
    faceTracker.setup();
}

void ControlMonitor::update(){
    faceTracker.update();
}

void ControlMonitor::draw(){
    ofSetColor(255);
    faceTracker.drawCam();
    ofDrawBitmapString("FPS: " + ofToString((int) ofGetFrameRate()), 10, 20);
    faceTracker.drawTracker();
    
    // easyCam.begin();
    ofSetupScreenOrtho(640, 480, -1000, 1000);
    ofTranslate(640 / 2, 480 / 2);
    
    ofPushMatrix();
    applyMatrix(faceTracker.rotationMatrix);
    ofScale(5,5,5);
//    faceTracker.drawFaceWire();
    
    ofNoFill();
    ofRect(-10, -10, 20, 20);
    ofDrawBitmapString("x: " + ofToString(faceTracker.orientation.x), 12, 0);
    ofDrawBitmapString("y: " + ofToString(faceTracker.orientation.y), 12, 6);
    ofDrawBitmapString("z: " + ofToString(faceTracker.orientation.z), 12, 12);
    
    ofPopMatrix();
    // easyCam.end();
}