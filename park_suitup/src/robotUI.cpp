#include "robotUI.h"

void robotUI::init(ofPoint pos_){
    for(int i = 0 ; i <NUM_IMAGE ; i++){
        char fileName[32];
        sprintf(fileName, "image/ironman0%d.png", i+1);
        robotImage[i].load(fileName);
    }
    pos = pos_;
}

void robotUI::update(){
}

void robotUI::draw(){
    ofxCvColorImage cv_img;
    
    ofPushMatrix();
    ofPushStyle();
    
    ofRotate(25, -0.3, 0.5, 0);
    robotImage[0].setAnchorPercent(0.5, 0.5);
    robotImage[0].draw(pos.x,pos.y);
    
    ofPopMatrix();
    ofPopStyle();
}