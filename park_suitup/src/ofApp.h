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
#include "comicFace.h"

#define NUM_SPECTRUM 5
#define MAXNUM_PARTICLE 1000

enum sceneMode{
    APP_START,              //0
    IN_SUIT_SCENE,          //1
    OPENING_START,          //2
    DOT_MOVIE,              //3
    SEPARATE_FACE,          //4
    PARTICLE_COLOR,         //5
    SOLID_BOX,              //6
    COMIC_FACE,             //7
    NORMAL_MOVIE,           //8
    ENDING                  //9
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
        ofSoundPlayer effectWarningPlayer;
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
        comicFace comicface;
    
        //for PARTICLE
        vector <particleScene> p;
        vector <ofPoint> attractPoints;
        vector <ofPoint> attractPointsWithMovement;
};