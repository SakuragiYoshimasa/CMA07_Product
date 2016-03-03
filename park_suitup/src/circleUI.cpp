#include "circleUI.h"


void circleUI::init(){
    for(int i = 0 ; i <NUM_IMAGE ; i++){
        char fileName[32];
        sprintf(fileName, "image/Circle%d.png", i+1);
        circleImage[i].load(fileName);
        
        angleCircle[i] = 10;
    }
    
    fix_angle = 0;
    
    //setupAnimator
    anim.reset(0.0f);
    anim.setRepeatType(LOOP_BACK_AND_FORTH);
    anim.setCurve(EASE_IN_EASE_OUT);
    anim.animateTo(1.0f);
}

void circleUI::update(int size_spect[]){
    for(int i = 0; i < NUM_IMAGE ; i++){
        angleCircle[i] += 5 * (i + 1);
        
        //reverse angleCircle[0],angleCircle[2]
        if(i%2 == 0){
            angleCircle[i] = -angleCircle[i];
        }
        sizeCircle[i] = size_spect[i] % ((int)circleImage[i].getWidth());
//        cout<<"sizeCircle"<<i<<":"<<sizeCircle[i]<<endl;
    }
    anim.update(1.0f/60.0f);
}

void circleUI::draw(){
    for(int i = 0 ; i < NUM_IMAGE; i++){
        ofPushMatrix();
        ofRotate(angleCircle[i]);
        
        float fixAnimSize = ofMap(anim.getCurrentValue(), 0.0, 1.0, 0.5, 1.0);
        
        circleImage[i].setAnchorPercent(0.5, 0.5);
        circleImage[i].draw(0,0,(CIRCLE_MAX_Z/2-(i*50)*anim.getCurrentValue()),
                            sizeCircle[i],circleImage[i].getHeight()*fixAnimSize);
        ofPopMatrix();
    }
}