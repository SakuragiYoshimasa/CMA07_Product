#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxGraphViewer.h"
#include "ofxAlphaMaskTexture.h"

#include "circleUI.h"
#include "graphUIBox.h"
#include "robotUI.h"
#include "particleScene.h"

#define NUM_SPECTRUM 5

enum sceneMode{
    APP_START,
    IN_SUIT_SCENE,
    CHANGE_SUIT
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    
    void setSceneMode();
    
    ofShader shader;
	
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
    
    //controlScene
    sceneMode sMode;
    int appTime;
    int sceneTime;
};