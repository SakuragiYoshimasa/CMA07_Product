//
//  ControlMonitor.h
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#ifndef ControlMonitor_h
#define ControlMonitor_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "FaceTracker.h"
#include "Config.h"

#define BUFSIZE 128

using namespace ofxCv;
using namespace cv;

class ControlMonitor{
public:
    void setup();
    void update();
    void draw(FaceTracker& faceTracker);
    void drawControlCircle(FaceTracker& faceTracker);
    void drawSoundWaveCircle(FaceTracker& faceTracker);
    void drawCircleMonitor(float angle, string label);
    void drawCrescentMonitor(float angle, string label);
    
    ControlMonitor();
    ~ControlMonitor(){};
    
//    FaceTracker faceTracker;
    Config conf;
    
    ofMatrix4x4 rotationMatrix;
    ofSpherePrimitive centerSphere;
    
    float buffer[BUFSIZE];
    int bufferSize;
    int time;
};

#endif /* ControlMonitor_h */
