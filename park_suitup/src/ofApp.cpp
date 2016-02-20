#include "ofApp.h"
#include "suitUIBox.h"
#include "ofxGraphViewer.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(1280, 720);
	
	tracker.setup();
	tracker.setRescale(.5);
    
    uibox.init(200,-400,200);
}

void ofApp::update() {
    uibox.updateUI();
	cam.update();
    
    ofPixels newPixels = cam.getPixels();
    ofPixels reversePixels;
    reversePixels.allocate(cam.getWidth(), cam.getHeight(), OF_PIXELS_BGR);
    
    for(int h = 0; h < cam.getHeight(); h++){
        for(int w = 0; w < cam.getWidth(); w++){
            reversePixels[h * cam.getWidth() * 3 + w * 3] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 - w) * 3];
            reversePixels[h * cam.getWidth() * 3 + w * 3 + 1] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 1];
            reversePixels[h * cam.getWidth() * 3 + w * 3 + 2] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 2];
        }
    }
    
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(reversePixels))) {
			classifier.classify(tracker);
		}		
	}
    
    reversePixels.clear();
    newPixels.clear();
}

void ofApp::draw() {
	ofSetColor(255);
    
    cam.draw(cam.getWidth(), 0, -cam.getWidth(), cam.getHeight());

    
    
    tracker.draw();
	
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
    
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
  for(int i = 0; i < n; i++){
		ofSetColor(i == primary ? ofColor::red : ofColor::black);
		ofDrawRectangle(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
  }
	ofPopMatrix();
	ofPopStyle();

    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(tracker.getPosition());
    ofMultMatrix(tracker.getRotationMatrix());

    ofDrawRectangle(200,100, 100 , 100);
    ofDrawRectangle(-300,100, 100 , 100);
    uibox.draw();
    
    ofPopMatrix();
    ofPopStyle();

	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapString(ofToString(tracker.getRotationMatrix()), ofGetWidth()/2, ofGetHeight() - 50);
	drawHighlightString(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n"
		"l - load expressions",
		14, ofGetHeight() - 7 * 12);
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
