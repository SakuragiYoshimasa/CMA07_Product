//
//  MidiControl.cpp
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/26/16.
//
//

#include "MidiControl.h"

MidiControl::MidiControl(){
    
}

void MidiControl::setup(){
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    //ofxMidiOut::listPorts(); // via static too
    
    // connect
    midiOut.openPort(0); // by number
    //midiOut.openPort("IAC Driver Pure Data In"); // by name
    //midiOut.openVirtualPort("o//); // open a virtual port
    
    channel = 2;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
    
    faceTracker.setup();
}

void MidiControl::update(){
    faceTracker.update();
    float value = ofMap(faceTracker.orientation.x,
                        -0.4, 0.4, 0.0, 127.0);
    midiOut.sendControlChange(channel, 16, value);
    
    value = ofMap(faceTracker.orientation.z,
                        -0.4, 0.4, 0.0, 127.0);
    midiOut.sendControlChange(channel, 17, value);
    time += 1;
}

void MidiControl::viewIndicator(){
    // let's see something
    ofSetColor(0);
    stringstream text;
    text << "connected to port " << midiOut.getPort()
    << " \"" << midiOut.getName() << "\"" << endl
    << "is virtual?: " << midiOut.isVirtual() << endl << endl
    << "sending to channel " << channel << endl << endl
    << "current program: " << currentPgm << endl << endl
    << "note: " << note << endl
    << "velocity: " << velocity << endl
    << "pan: " << pan << endl
    << "bend: " << bend << endl
    << "touch: " << touch << endl
    << "polytouch: " << polytouch;
    ofDrawBitmapString(text.str(), 20, 20);
    
    ofDrawBitmapString(ofToString(ofMap(faceTracker.orientation.x, -0.4, 0.4, 0.0, 127.0)), 20, 0);
    ofDrawBitmapString(ofToString(ofMap(faceTracker.orientation.z, -0.4, 0.4, 0.0, 127.0)), 80, 0);
}

void MidiControl::exit(){
    midiOut.closePort();
}

void MidiControl::mouseDragged(int x, int y, int button) {
    
    // x pos controls the pan (ctl = 10)
    pan = ofMap(x, 0, ofGetWidth(), 0, 127);
    midiOut.sendControlChange(channel, 16, pan);
    
    // y pos controls the pitch bend
    bend = ofMap(y, 0, ofGetHeight(), 0, MIDI_MAX_BEND);
    midiOut.sendPitchBend(channel, bend);
}

void MidiControl::controlWave(int control, float t){
    pan = 64 + 63 * sin(time * t);
    midiOut.sendControlChange(channel, control, pan);
}

