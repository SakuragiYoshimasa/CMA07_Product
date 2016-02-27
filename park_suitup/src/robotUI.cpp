#include "robotUI.h"

void robotUI::init(ofPoint pos_){
    for(int i = 0 ; i <NUM_IMAGE ; i++){
        char fileName[32];
        sprintf(fileName, "image/ironman0%d.png", i+1);
        robotImage[i].load(fileName);
    }
    pos = pos_;
    
    moveCircleZ = 0;
}

void robotUI::update(){
    //update moveCircleY
    moveCircleZ =  (pos.y/2) + (pos.y/2)*sin(ofMap(ofGetElapsedTimeMillis(), 0, 10000, 0, 2*PI));
    moveCircleZ =  ofMap(moveCircleZ, 0, pos.y, -(pos.y/2), (pos.y/2));
}

void robotUI::draw(){
    ofPushStyle();
    ofPushMatrix();
    
    //draw RobotImage
    robotImage[0].setAnchorPercent(0.5, 0.5);
    ofRotateZ(-15);
    robotImage[0].draw(pos);

    //draw moveCircle
    ofSetColor(0,255,0,50);
    ofNoFill();
    ofSetLineWidth(2);
    ofTranslate(pos);
    ofRotateX(260);
    ofRotateY(170);

    for(int i = 0 ; i < NUM_CIRCLE ; i++){
        ofDrawCircle(0,0,moveCircleZ-10*(i-NUM_CIRCLE/2), 100);
    }
    
    ofPopMatrix();
    ofPopStyle();
}