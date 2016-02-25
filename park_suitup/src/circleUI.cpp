#include "circleUI.h"


void circleUI::init(){
    for(int i = 0 ; i <NUM_IMAGE ; i++){
        char fileName[32];
        sprintf(fileName, "image/Circle%d.png", i+1);
        circleImage[i].load(fileName);
        
        angleCircle[i] = 10;
    }
    
    fix_angle = 0;
}

void circleUI::updateUI(){
    for(int i = 0; i < NUM_IMAGE ; i++){
        angleCircle[i] += 5 * (i + 1);
        if(i%2 == 0){
            angleCircle[i] = -angleCircle[i];
        }
    }
}

void circleUI::draw(){
    for(int i = 0 ; i < NUM_IMAGE; i++){
        ofPushMatrix();
        ofRotate(angleCircle[i]);
        
        circleImage[i].setAnchorPercent(0.5, 0.5);
        circleImage[i].draw(0,0);
        
        ofPopMatrix();
    }
}