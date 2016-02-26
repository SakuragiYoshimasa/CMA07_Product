#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxGraphViewer.h"
#include "ofxAlphaMaskTexture.h"

#include "circleUI.h"
#include "graphUIBox.h"
#include "robotUI.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    
    ofxAlphaMaskTexture *alphaMask;
    ofImage maskImg;
    ofImage bottomImg;
    
    graphUIBox uibox;
    circleUI eyeCircle;
    robotUI robot;
};