//
//  FaceTracker.cpp
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#include "FaceTracker.h"

FaceTracker::FaceTracker(){
    
}

void FaceTracker::setup(){
    cam.initGrabber(conf.camWidth, conf.camHeight);
    tracker.setup();
}

void FaceTracker::update(){
    cam.update();
    if(cam.isFrameNew()) {
        Mat camMirrored;
        flip(toCv(cam), camMirrored, 1);
        tracker.update(toCv(camMirrored));
        position = tracker.getPosition();
        scale = tracker.getScale();
        orientation = tracker.getOrientation();
        rotationMatrix = tracker.getRotationMatrix();
    }
}

void FaceTracker::reset(){
    tracker.reset();
}

void FaceTracker::drawCam(){
    cam.draw(conf.camWidth, 0, -conf.camWidth, conf.camHeight);
}

void FaceTracker::drawTracker(){
    if(tracker.getFound()) {
    	ofSetLineWidth(1);
    	tracker.draw();
    }
}

void FaceTracker::drawFaceWire(){
    if(tracker.getFound()) {
         tracker.getObjectMesh().drawWireframe();
    }
}

bool FaceTracker::getFound(){
    return tracker.getFound();
}

bool FaceTracker::getMouseOpend(){
    float mouseHeight = getGesture(ofxFaceTracker::MOUTH_HEIGHT);
    if (mouseHeight > conf.mouseOpenedHeightThreshold) {
        return true;
    }
    return false;
}

float FaceTracker::getGesture(ofxFaceTracker::Gesture gesture){
    return tracker.getGesture(gesture);
}

