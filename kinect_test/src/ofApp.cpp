#include "ofApp.h"
//#include "ofxKinect.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    if (!kinect.isConnected()) {
        ofSystemAlertDialog("Serial Error : Kinect is not connected. Check a usb port then push space bar.");
    }
    

    ofxGuiSetDefaultHeight(300);
    ofxGuiSetDefaultWidth(18);
    gui.setup("Depth Masking Control");
    gui.setPosition(10,10);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    //kinect.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (kinect.isFrameNew()) {
        cameraImage.setFromPixels(kinect.getPixels(), kinect.width, kinect.height, OF_IMAGE_COLOR);
        
        depthImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
    }
    
    cameraImage.draw(0,0,kinect.width,kinect.height);
    depthImage.draw(0,kinect.height,kinect.width/2,kinect.height/2);
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case ' ':
            kinect.init();
            kinect.open();
            if (!kinect.isConnected()) {
                ofSystemAlertDialog("Serial Error : Kinect is not connected. Check a usb port then push space bar.");
            }
            break;
            
//        default:
            break;
    }

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
