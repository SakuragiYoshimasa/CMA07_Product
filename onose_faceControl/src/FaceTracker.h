//
//  FaceTracker.h
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#ifndef FaceTracker_h
#define FaceTracker_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "Config.h"

using namespace ofxCv;
using namespace cv;

class FaceTracker{
public:
    FaceTracker();
    ~FaceTracker(){};
    void setup();
    void update();
    void reset();
    void drawCam();
    void drawTracker();
    void drawFaceWire();
    bool getFound();
    bool getMouseOpend();
    float getGesture(ofxFaceTracker::Gesture gesture);
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;
    
    Mat translation, rotation;
    ofMatrix4x4 pose;
    
    ofEasyCam easyCam;
    
    Config conf;
};

#endif /* FaceTracker_h */
