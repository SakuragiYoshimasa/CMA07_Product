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
    rainY1 = ofRandom(-ofGetHeight(),-100.0);
    rainY2 = rainY1 + ofRandom(10.0, 100.0);
    speed_y =  ofRandom(10.0, 30.0);
    linewidth = ofRandom(ofRandom(0.1,2.0));
    
    switch (int(ofRandom(3))) {
        case 0:
            rainHue.setHsb(50*2.25, 255, 255, ofRandom(100,255));
            break;
        case 1:
            rainHue.setHsb(55*2.25, 255, 255, ofRandom(100,255));
            break;
        case 2:
            rainHue.setHsb(60*2.25, 255, 255, ofRandom(100,255));
            break;
    }
}

void Drop::update(){
    
    rainY1 += speed_y;
    rainY2 += speed_y;
    
    if (rainY1 > ofGetHeight()) {
        rainY1 = -100.0;
        rainY2 = rainY1 + ofRandom(10.0, 100.0);
    }
}

void Drop::draw(){
    ofPushStyle();

    ofSetLineWidth(linewidth);
    //ofSetColor(ofRandom(255), ofRandom(255) ,ofRandom(255));
    ofSetColor(rainHue);
    ofLine(rainX, rainY1, rainX, rainY2);
    
    ofPopStyle();
}