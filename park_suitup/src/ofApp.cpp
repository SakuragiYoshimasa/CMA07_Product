#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    
    //setup Camera
	cam.initGrabber(1280, 720);
    
    maskImg.load("image/mask.jpg");
    bottomImg.load("image/bottomimage.jpg");

    alphaMask = new ofxAlphaMaskTexture(cam.getTexture(),       // top layer texture
                                        bottomImg.getTexture(), // bottom layer texture
                                        maskImg.getTexture());  // mask layer texture
	
    //seup Facetracker
	tracker.setup();
	tracker.setRescale(.5);
    
    //setup UI
    eyeCircle.init();
    
    uibox_b.init(ofPoint(ofGetWidth()/2 + 100, 400),'b');
    uibox_t.init(ofPoint(ofGetWidth()/2 + 100, 10),'t');
    robot.init(ofPoint(20,500));
}

void ofApp::update() {
    //update UI
    uibox_b.update();
    uibox_t.update();
    robot.update();
    eyeCircle.update();
    
    //update Camera
	cam.update();
    
    alphaMask->maskScale =  ofMap(tracker.getScale(),0.0,10.0,0.0,1.0);

	if(cam.isFrameNew()) {
        ofPixels newPixels = cam.getPixels();
        ofPixels reversePixels;
        reversePixels.allocate(cam.getWidth(), cam.getHeight(), OF_PIXELS_BGR);
        
        //reverse cam pixels
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
            uibox_b.setModesize(1);
            uibox_t.setModesize(1);
        }else if(angleFace.y > 0){
            uibox_b.setModesize(2);
            uibox_t.setModesize(2);
        }
    }
}

void ofApp::draw() {
	ofSetColor(255);
    
//    cam.draw(cam.getWidth(), 0, -cam.getWidth(), cam.getHeight());
    
    ofPushStyle();
    ofPushMatrix();
    
    ofScale(-1,1);
    ofTranslate(-cam.getWidth(),0);
    alphaMask->draw();
    
    ofPopMatrix();
    ofPopStyle();

    if(tracker.getHaarFound()){
        
        if(tracker.getImagePoint(42) != tracker.getImagePoint(45)){
            
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
        }

        
        //draw stand UI
        ofPushStyle();
        ofPushMatrix();
        
//        ofTranslate(ofGetWidth()/2, 0);
        
        //lineGraph
        uibox_b.draw();
        uibox_t.draw();
        robot.draw();

        ofPopMatrix();
        ofPopStyle();
    }

    
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapString(ofToString(tracker.getScale()), ofGetWidth()/2, ofGetHeight() - 50);
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
