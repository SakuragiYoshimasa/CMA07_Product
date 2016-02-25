#include "ofMain.h"
#include "ofxGraphViewer.h"

#pragma once

#define GRAPHUI_MIN_SIZE 150
#define GRAPHUI_MAX_SIZE 400

class graphUIBox {
private:
    ofPoint pos;
    int size_box;
    int fix_size_box;
    int mode_size;
    
public:
    void init(ofPoint pos_);
    void update();
    void setModesize(int mode_size_);
    void draw();
    
    ofxGraphViewer gViewer;
    float d ;
};