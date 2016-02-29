#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxMidi.h"
#include "ControlMonitor.h"
#include "MidiControl.h"
#include "FaceTracker.h"

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
    void audioReceived(float *buf, int bufSize, int nChan);
    
    MidiControl midiControl;
    ControlMonitor controlMonitor;
    
    ofxMidiOut midiOut;
    FaceTracker faceTracker;
    
    // Sound
    ofSoundPlayer mySound;
    ofSoundStream soundStream;
    float * fft;           //FFT解析結果を格納する配列
    int nBandsToGet;       //FFT解析の分解精度
};
