#include "ofMain.h"
#include "ofxGraphViewer.h"
#include "ofxFboBlur.h"

#pragma once

#define GRAPHUI_MIN_SIZE 150
#define GRAPHUI_MAX_SIZE 300
#define GRAPHUI_ANGLE    30

class graphUIBox {
private:
    ofPoint pos;
    float angle;
    
    int size_box;
    int fix_size_box;

    int mode_size;
    char mode_pos;

    
public:
    void init(ofPoint pos_, char mode_pos_);
    void update();
    void setModesize(int mode_size_);
    void draw();
    
    ofxGraphViewer gViewer;
    int d;
//    float d ;
    
    ofxFboBlur gpuBlur;
};