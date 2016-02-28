//
//  Bounce.cpp
//  BouncingWater
//
//  Created by 片山怜 on 2016/02/24.
//
//

#include "Bounce.hpp"

Bounce::Bounce(){
    
    gravity = 3;
    lifetime = ofRandom(300,500);
    time = 0;
    
    switch (int(ofRandom(4))) {
        case 0:
            hue.setHsb(50*2.25, 255, 200, ofRandom(100,255));
            break;
        case 1:
            hue.setHsb(55*2.25, 255, 200, ofRandom(100,255));
            break;
        case 2:
            hue.setHsb(60*2.25, 255, 200, ofRandom(200,255));
            break;
        case 3:
            hue.setHsb(0, 0, 255, ofRandom(100,255));
    }
    
    for (int i = 0; i < NUM; i++) {
        
        speed_y[i] = ofRandom(-30,-10);
        loc_x[i] = ofRandom(ofGetWidth());
        loc_y[i] = ofRandom(ofGetHeight()-50,ofGetHeight()+100);
        radius[i] = ofRandom(0.3,20);
    }
}

void Bounce::update(){
    
    time++;
    
    for (int i = 0; i < NUM; i++){
        
        speed_y[i] += gravity;
        loc_y[i] += speed_y[i];
    }
}

void Bounce::draw(){
    
    ofSetColor(hue);
    
    for (int i = 0; i < NUM; i++) {
        ofCircle(loc_x[i], loc_y[i], radius[i]);
    }
}