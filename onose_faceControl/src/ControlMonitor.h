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

using namespace ofxCv;
using namespace cv;

class ControlMonitor{
public:
    void setup();
    void update();
    void draw();
    
    ControlMonitor();
    ~ControlMonitor(){};
    
    FaceTracker faceTracker;
    Config conf;
};

#endif /* ControlMonitor_h */
