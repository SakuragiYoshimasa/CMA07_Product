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
    
    channel = conf.channel;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = 0;
    touch = 0;
    polytouch = 0;
    
}

void MidiControl::update(){

    time += 1;
}

void MidiControl::keyPressed(int key){
    switch (key) {
        case '1':
            conf.xCtrl *= -1;
            break;
        case '2':
            conf.yCtrl1 *= -1;
            break;
        case '3':
            conf.yCtrl2 *= -1;
            break;
        default:
            break;
    }
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

void MidiControl::sendControlChange(int control, float value, float valMin, float valMax){
    float controlValue = ofMap(value, valMin, valMax, 0, 127);
    if(controlValue < 0)    controlValue = 0;
    if(controlValue > 127)  controlValue = 127;
    midiOut.sendControlChange(channel, control, controlValue);
}

void MidiControl::faceOriControl(FaceTracker& faceTracker){
    if (conf.xCtrl > 0) {
        sendControlChange(16, faceTracker.orientation.x,
                          conf.faceOriXThreshold, -conf.faceOriXThreshold);
    }
    if (conf.yCtrl1 > 0){
        if(faceTracker.orientation.y < 0){
            sendControlChange(17, faceTracker.orientation.y,
                              0, -conf.faceOriYThreshold);
        }
    }
    if (conf.yCtrl2 > 0){
        if(faceTracker.orientation.y > 0){
            sendControlChange(18, faceTracker.orientation.y,
                              0, conf.faceOriYThreshold);
        }
    }
}

void MidiControl::mouseControl(FaceTracker& faceTracker){
    if(faceTracker.getMouseOpend()){
        midiOut.sendNoteOn(channel, 64, 64);
    }
}

