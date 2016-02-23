#include "ofApp.h"
#include "Drop.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetWindowShape(ofGetWidth(), ofGetHeight());
    
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
    
    //raintestよりペースト
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    ofSetLineWidth(ofRandom(1.0,3.0));
    
    
    for (int i=0 ;i<100; i++) {
        rain.push_back(*new Drop());
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    
///////わからない場所/////////////////////////////////////////////////////////////////////////
    for(int i=0; i < rain.size(); i++){
        rain[i].update();
    
        if (kinect.getNumTrackedUsers() > 0) {
            ofxOpenNIUser user = kinect.getTrackedUser(0);
            
    
            for (int j = 0; j < 6; j++) {
                ofxOpenNILimb limb = user.getLimb(need_limb_id[j]);
                
                if (limb.isFound()) {
                    float x1 = limb.getStartJoint().getProjectivePosition().x;
                    float y1 = limb.getStartJoint().getProjectivePosition().y;
                    float x2 = limb.getEndJoint().getProjectivePosition().x;
                    float y2 = limb.getEndJoint().getProjectivePosition().y;
                
                //rainXがlimbの範囲内にあるかどうか
                if ( (rain[i].rainX > x1  && rain[i].rainX < x2) || (rain[i].rainX > x2  && rain[i].rainX < x1)) {
                
                
                //rainY2がlimbの座標にあるかどうか
                if ((rain[i].rainY2 < (ofMap ( rain[i].rainX, x1, x2, y1, y2 ))+20)
                    && rain[i].rainY2 > (ofMap ( rain[i].rainX, x1, x2, y1, y2 ))-20){
    
                    rain[i].rainY1 = -100.0;
                    rain[i].rainY2 = rain[i].rainY1 + ofRandom(10.0, 100.0);
                    }
                }
            }
        }
    }
}
}
///////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //  draw RGB image (weak)
    ofSetColor(100, 100, 100);
    kinect.drawImage(0, 0, ofGetWidth(), ofGetHeight());
    
    //  normal color
    ofSetColor(255, 255, 255);
    
    //  draw user
    
    for(int i=0; i < rain.size(); i++){
        rain[i].draw();
    }
    
    
    if (kinect.getNumTrackedUsers() > 0) {
        
        //  skeleton data
        ofxOpenNIUser user = kinect.getTrackedUser(0);
        
        //  draw two arms
        ofSetLineWidth(5);
        ofSetColor(255, 255, 255);
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