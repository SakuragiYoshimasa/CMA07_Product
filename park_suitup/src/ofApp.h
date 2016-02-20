#pragma once

#include "ofMain.h"
#include "graphUIBox.h"
#include "ofxFaceTracker.h"
#include "ofxGraphViewer.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    graphUIBox uibox;
};