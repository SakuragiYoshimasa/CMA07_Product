//
//  Drop.cpp
//  test_rain&kinect
//
//  Created by 片山怜 on 2016/02/21.
//
//

#include "Drop.hpp"
#include "ofmain.h"

Drop::Drop(){
    
    rainX = ofRandom(5.0,ofGetWidth()-5.0);
    rainY1 = ofRandom(-ofGetWidth(),-100.0);
    rainY2 = rainY1 + ofRandom(10.0, 100.0);
    speed_y =  ofRandom(10.0, 30.0);
}

void Drop::update(){
    
    rainY1 = rainY1 + speed_y;
    rainY2 = rainY2 + speed_y;
    
    if (rainY1 > ofGetHeight()) {
        rainY1 = -100.0;
        rainY2 = rainY1 + ofRandom(10.0, 100.0);
    }
}

void Drop::draw(){
    
    ofSetColor(ofRandom(255), ofRandom(255) ,ofRandom(255));
    ofLine(rainX, rainY1, rainX, rainY2);
    
}