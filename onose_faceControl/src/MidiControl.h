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
#include "FaceTracker.h"
#include "ControlMonitor.h"

class MidiControl{
public:
    void setup();
    void update();
    void viewIndicator();
    void exit();
    void mouseDragged(int x, int y, int button);
    void controlWave(int control, float t);
    
    MidiControl();
    ~MidiControl(){};
    
    ofxMidiOut midiOut;
    FaceTracker faceTracker;
    int channel;
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    int time = 0;
};

#endif /* MidiControl_h */
