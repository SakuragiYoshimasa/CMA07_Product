#include "ofMain.h"
#include "ofxGraphViewer.h"

#pragma once

class suitUIBox {
private:
    ofColor color;
    ofPoint pos;
    int size_box;
    
public:
    void init(float x, float y, int size);
    void updateUI();
    void draw();
    ofxGraphViewer gViewer;
    float d ;
};