#include "ofApp.h"
#include "Drop.hpp"


//--------------------------------------------------------------
void ofApp::setup() {
    
    rain.setup();
    
    
    /* //     window
     ofBackground(0, 0, 0);
     ofSetWindowShape(640, 480);
     ofSetFrameRate(30);*/
    
    
    //  setup ofxOpenNI
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addImageGenerator();     //  required for RGB image
    kinect.addDepthGenerator();     //  required for depth image
    kinect.addUserGenerator();      //  required for skeleton tracking
    kinect.setMaxNumUsers(1);       //  max num of skeleton to track
    
    
    //  start kinect
    kinect.start();
    
    for (int i=0 ;i<100; i++) {
        rainCount.push_back(*new Drop());
    }
    
    //raintestよりペースト
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    ofSetLineWidth(ofRandom(1.0,3.0));
    

    //ofSetWindowShape(640, 480);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    rain.update();
    
    
    //   if (rainX > /*ここに始点X*/ && rainX < /*ここに終点X*/) {
    //            if ((rainY2 < (ofMap(rainX, /*ここに始点X*/ ,  /*ここに終点X*/, /*ここに始点Y*/ , /*ここに終点Y*/ ))+20)
    //                && rainY2 > (ofMap(rainX, /*ここに始点X*/ ,  /*ここに終点X*/, /*ここに始点Y*/ , /*ここに終点Y*/ ))-20){
    //
    //                rainY1 = -100.0;
    //                rainY2 = rainY1 + ofRandom(10.0, 100.0);
    //            }
    //        }
    //    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    rain.draw();
    
    
    //  draw RGB image (weak)
    ofSetColor(100, 100, 100);
    kinect.drawImage(0, 0, ofGetWidth(), ofGetHeight());
    
    //  normal color
    ofSetColor(255, 255, 255);
    
    //  draw user
    
    if (kinect.getNumTrackedUsers() > 0) {
        
        //  skeleton data
        ofxOpenNIUser user = kinect.getTrackedUser(0);
        
        //  draw two arms
        ofSetLineWidth(5);
        ofSetColor(0, 0, 0);
        for (int i = 0; i < 6; i++) {
            ofxOpenNILimb limb = user.getLimb(need_limb_id[i]);
            if (limb.isFound()) {
                float x1 = limb.getStartJoint().getProjectivePosition().x;
                float y1 = limb.getStartJoint().getProjectivePosition().y;
                float x2 = limb.getEndJoint().getProjectivePosition().x;
                float y2 = limb.getEndJoint().getProjectivePosition().y;
                ofLine(x1, y1, x2, y2);
            }
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    
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