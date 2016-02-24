//
//  Bounce.cpp
//
//  Created by 片山怜 on 2016/02/24.
//
//

#include "Bounce.hpp"

Bounce::Bounce(){
    
    gravity = 1;
    
    for (int i = 0; i < NUM; i++) {
        
        speed_y[i] = -30;
        loc_x[i] = ofRandom(ofGetWidth());
        loc_y[i] = ofRandom(ofGetHeight(),ofGetHeight()-500);
        radius[i] = ofRandom(1,20);
    }
}

void Bounce::update(){
    
    
    for (int i = 0; i < NUM; i++) {
        
        speed_y[i] += gravity;
        loc_y[i] += speed_y[i];
    }
}

void Bounce::draw(){
    for (int i = 0; i < NUM; i++) {
        
        ofCircle(loc_x[i], loc_y[i], radius[i]);
    }
}