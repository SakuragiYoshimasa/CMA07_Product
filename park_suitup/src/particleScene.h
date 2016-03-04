#pragma once
#include "ofMain.h"

class particleScene{
    
public:
    particleScene();
    
    void reset();
    void update(ofPoint facePosition);
    void draw(ofVideoPlayer video);
    
    ofPoint pos;
    ofPoint vel;

    float scale;

};