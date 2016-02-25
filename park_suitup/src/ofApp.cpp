#include "ofApp.h"
#include "ofxGraphViewer.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
	cam.initGrabber(1280, 720);
	
	tracker.setup();
	tracker.setRescale(.5);

    uibox.init(400,200);
    eyeCircle.init();
}

void ofApp::update() {
    uibox.updateUI();
    eyeCircle.updateUI();
    
	cam.update();

	if(cam.isFrameNew()) {
        ofPixels newPixels = cam.getPixels();
        ofPixels reversePixels;
        reversePixels.allocate(cam.getWidth(), cam.getHeight(), OF_PIXELS_BGR);
        
        //reverse cam
        for(int h = 0; h < cam.getHeight(); h++){
            for(int w = 0; w < cam.getWidth(); w++){
                reversePixels[h * cam.getWidth() * 3 + w * 3] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 - w) * 3];
                reversePixels[h * cam.getWidth() * 3 + w * 3 + 1] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 1];
                reversePixels[h * cam.getWidth() * 3 + w * 3 + 2] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 2];
            }
        }
        
		if(tracker.update(toCv(reversePixels))) {
			classifier.classify(tracker);
		}
        
        reversePixels.clear();
        newPixels.clear();
    }
    
    if(tracker.getHaarFound()){
        ofVec3f angleFace = tracker.getRotationMatrix().getRotate().getEuler();
        
        //control_ui_right
        if(angleFace.y < 0){
            uibox.setModesize(1);
        }else if(angleFace.y > 0){
            uibox.setModesize(2);
        }
    }
    
    
}

void ofApp::draw() {
	ofSetColor(255);
    
    cam.draw(cam.getWidth(), 0, -cam.getWidth(), cam.getHeight());
    
//    tracker.draw();

    //draw movalbe UI
    ofPushStyle();
    ofPushMatrix();
    ofPoint eyePos = (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2;
    ofTranslate(eyePos);
    
    //reverseMatrix
    ofMatrix4x4 reverseMatrix;
    ofQuaternion newMatrix = tracker.getRotationMatrix().getRotate();
    
    newMatrix.set(-newMatrix.x(), -newMatrix.y(), newMatrix.z(), newMatrix.w());
    reverseMatrix.setRotate(newMatrix);
    ofMultMatrix(reverseMatrix);
    
    eyeCircle.draw();
    
    ofPopMatrix();
    ofPopStyle();
    
    //draw stand UI
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //right_bottom_lineGraph
    ofRotate(25, -0.3, 0.5, 0);
    uibox.draw();
    
    ofPopMatrix();
    ofPopStyle();

    
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapString(ofToString(tracker.getPosition()), ofGetWidth()/2, ofGetHeight() - 50);
}

void ofApp::keyPressed(int key) {
    switch(key){
        case 'r'    :
            tracker.reset();
            classifier.reset();
            break;
        case 'e'    :
            classifier.addExpression();
            break;
        case 'a'    :
            classifier.addSample(tracker);
            break;
        case 's'    :
            classifier.save("expressions");
            break;
        case 'l'    :
            classifier.load("expressions");
            break;
    }
}
