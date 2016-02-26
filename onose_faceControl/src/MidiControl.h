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

class MidiControl{
public:
    void setup();
    void viewIndicator();
    void exit();
    void mouseDragged(int x, int y, int button);

    
    MidiControl();
    ~MidiControl(){};
    
//    ofxMidiOut midiOut;
    int channel;
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
};

#endif /* MidiControl_h */
