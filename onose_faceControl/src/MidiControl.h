//
//  MidiControl.h
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/26/16.
//
//

#ifndef MidiControl_h
#define MidiControl_h

#include "ofMain.h"
#include "ofxMidi.h"
#include "Config.h"
#include "ControlMonitor.h"
#include "FaceTracker.h"

class MidiControl{
public:
    void setup();
    void update();
    void viewIndicator();
    void exit();
    void mouseDragged(int x, int y, int button);
    void controlWave(int control, float t);
    void sendControlChange(int control, float value, float valMin, float valMax);
    void faceOriControl(FaceTracker& faceTracker);
    
    MidiControl();
    ~MidiControl(){};
    
    ofxMidiOut midiOut;
    int channel;
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    int time = 0;
    
    Config conf;
};

#endif /* MidiControl_h */
