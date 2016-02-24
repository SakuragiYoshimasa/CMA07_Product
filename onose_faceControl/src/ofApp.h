#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ControlMonitor.h"
using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
    ControlMonitor controlMonitor;
};
