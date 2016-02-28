#include "ofApp.h"
#include "Drop.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    
    //ofSetWindowShape(ofGetWidth(), ofGetHeight());
    
    //  setup ofxOpenNI
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addImageGenerator();     //  required for RGB image
    kinect.addDepthGenerator();     //  required for depth image
    kinect.addUserGenerator();      //  required for skeleton tracking
    kinect.setMaxNumUsers(1);       //  max num of skeleton to track
    kinect.setResolution(ofGetWidth(), ofGetHeight(), 30); //Kinectの描画を大きくする（？）
    
    //  start kinect
    kinect.start();
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(30);
    ofSetLineWidth(Drop().linewidth);
    ofSetCircleResolution(64);
    
    soundplayer.loadSound("Problem - Pentatonix.mp3");
    soundplayer.setLoop(false);
    soundplayer.setVolume(1.0);
    soundplayer.play();
    
    
    for (int i=0 ;i<500; i++) {
        rain.push_back(*new Drop());
    }
    
    jointHue.setHsb(55*2.25, 255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    
    //Drop
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
                if ( (rain[i].rainX > x1*Ratio  && rain[i].rainX < x2*Ratio ) || (rain[i].rainX > x2*Ratio   && rain[i].rainX < x1*Ratio )) {
                
                
                //rainY2がlimbの座標にあるかどうか
                if ((rain[i].rainY2 < (ofMap ( rain[i].rainX, x1*Ratio , x2*Ratio , y1*Ratio , y2*Ratio  ))+20)
                    && rain[i].rainY2 > (ofMap ( rain[i].rainX, x1*Ratio , x2*Ratio , y1*Ratio , y2*Ratio  ))-20){
    
                    rain[i].rainY1 = -100.0;
                    rain[i].rainY2 = rain[i].rainY1 + ofRandom(10.0, 100.0);
                    }
                }
            }
        }
    }
}
    //Bounce
    volume = ofSoundGetSpectrum(1);
    if (volume[0] > 0.045) {
        bounces.push_back(*new Bounce());
    }
    
    for(int i=0; i < bounces.size(); i++){
        bounces[i].update();
        if(bounces[i].time > bounces[i].lifetime){
            bounces.pop_front();
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    //  draw RGB image (weak)
    ofSetColor(0, 0, 0);
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
        
        
/*腕のみの描画    
                for (int i = 0; i < 6; i++) {
                    ofxOpenNILimb limb = user.getLimb(need_limb_id[i]);
                    if (limb.isFound()) {
                        float x1 = limb.getStartJoint().getProjectivePosition().x;
                        float y1 = limb.getStartJoint().getProjectivePosition().y;
                        float x2 = limb.getEndJoint().getProjectivePosition().x;
                        float y2 = limb.getEndJoint().getProjectivePosition().y;
                        ofLine(x1*Ratio , y1*Ratio , x2*Ratio , y2*Ratio );
                    }
                }*/
        
        
        for (int i = 0; i < user.getNumLimbs(); i++) {
            ofxOpenNILimb limb = user.getLimb((enum Limb) i);
            if (limb.isFound()) {
                float x1 = limb.getStartJoint().getProjectivePosition().x;
                float y1 = limb.getStartJoint().getProjectivePosition().y;
                float x2 = limb.getEndJoint().getProjectivePosition().x;
                float y2 = limb.getEndJoint().getProjectivePosition().y;
                ofLine(x1*Ratio, y1*Ratio, x2*Ratio, y2*Ratio);
                
                
                
                
            }
        }
        
        //  draw joints
        ofSetColor(jointHue);
        for (int i = 0; i < user.getNumJoints(); i++) {
            ofxOpenNIJoint joint = user.getJoint((enum Joint) i);
            if (joint.isFound()) {
                float x = joint.getProjectivePosition().x;
                float y = joint.getProjectivePosition().y;
                ofCircle(x*Ratio, y*Ratio, 20);
            }
        }
        
        ofSetColor(jointHue);
        ofxOpenNIJoint joint = user.getJoint(JOINT_HEAD);
        if (joint.isFound()) {
            float head_x = joint.getProjectivePosition().x;
            float head_y = joint.getProjectivePosition().y;
            ofCircle(head_x*Ratio, head_y*Ratio, 35);
        }
    }
    for(int i=0; i < bounces.size(); i++){
        bounces[i].draw();
    }
}
//--------------------------------------------------------------
void ofApp::exit(){
    kinect.stop();
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