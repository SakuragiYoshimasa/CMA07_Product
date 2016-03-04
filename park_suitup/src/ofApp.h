#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxGraphViewer.h"
#include "ofxAlphaMaskTexture.h"

#include "circleUI.h"
#include "graphUIBox.h"
#include "robotUI.h"

#include "particleScene.h"
#include "dotMovie.h"
#include "separateFace.h"
#include "solidBox.h"

#define NUM_SPECTRUM 5
#define MAXNUM_PARTICLE 1000

enum sceneMode{
    APP_START,
    IN_SUIT_SCENE,
    OPENING_START,
    DOT_MOVIE,
    SEPARATE_FACE,
    PARTICLE_COLOR,
    SOLID_BOX,
    ENDING
};

class ofApp : public ofBaseApp {
    private :
    public :
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
        
        void setSceneMode();
    
        //for shader
        ofShader shader;
    
        //for FaceTracker
        ofVideoGrabber cam;
        ofxFaceTracker tracker;
        ExpressionClassifier classifier;
    
        //for Mask
        ofxAlphaMaskTexture *alphaMask;
        ofImage maskImg;
        ofImage bottomImg;
    
        //for Movie
        ofVideoPlayer openingMovie;
        ofVideoPlayer mainMovie;
        ofVideoPlayer interfaceMovie;
    
        //for Sound
        ofSoundPlayer suitBgmPlayer;
        ofSoundPlayer mainBgmPlayer;
        int size_spect[NUM_SPECTRUM];
    
        //controlScene
        sceneMode sMode;
        int appTime;
        int sceneTime;
        
        vector<float> timeTable;
        vector<sceneMode> sceneTable;
        int numTimeTable;
        int numSceneTable;
    
        //for IN_SUIT_SCENE
        graphUIBox uibox_b;
        graphUIBox uibox_t;
        circleUI eyeCircle;
        robotUI robot;
    
        //for Effect_SCENE
        dotMovie dotmovie;
        separateFace separateface;
        solidBox solidbox;
    
        //for PARTICLE
        vector <particleScene> p;
        vector <ofPoint> attractPoints;
        vector <ofPoint> attractPointsWithMovement;
};