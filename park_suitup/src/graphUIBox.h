#include "ofMain.h"
#include "ofxGraphViewer.h"

#pragma once

#define GRAPHUI_MIN_SIZE 200
#define GRAPHUI_MAX_SIZE 500

class graphUIBox {
private:
    ofColor color;
    ofPoint pos;
    int size_box;
    int fix_size_box;
    int mode_size;
    
public:
    void init(float x, float y);
    void updateUI();
    void setModesize(int mode_size_);
    void draw();
    
    ofxGraphViewer gViewer;
    float d ;
};