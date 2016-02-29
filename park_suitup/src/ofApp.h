#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxGraphViewer.h"
#include "ofxAlphaMaskTexture.h"

#include "circleUI.h"
#include "graphUIBox.h"
#include "robotUI.h"

#define NUM_SPECTRUM 5

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
    
    ofSoundPlayer bgmPlayer;
    int size_spect[NUM_SPECTRUM];
    
    graphUIBox uibox_b;
    graphUIBox uibox_t;
    circleUI eyeCircle;
    robotUI robot;
};