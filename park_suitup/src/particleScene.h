#pragma once
#include "ofMain.h"

class particleScene{
    
public:
    void init();
    void setAttractPoints(vector <ofPoint> * attract);
    
    void reset();
    void update();
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    float scale;
    
    vector <ofPoint> * attractPoints;
};