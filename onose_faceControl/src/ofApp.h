#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ControlMonitor.h"
#include "MidiControl.h"

using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp {
public:
	void setup();
    void exit();
	void update();
	void draw();
	void keyPressed(int key);
    void mouseDragged(int x, int y, int button);

	
    MidiControl midiControl;
    ControlMonitor controlMonitor;
    
    
};
