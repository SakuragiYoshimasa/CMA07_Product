#include "graphUIBox.h"


void graphUIBox::init(ofPoint pos_){
    pos = pos_;
    
    size_box = GRAPHUI_MAX_SIZE/2;
    fix_size_box = 0;
    mode_size = 0;
    
    d = 0;
    
    gViewer.setup(512);
    gViewer.setRange(-2.0, 2.0);
    gViewer.setSize(size_box * 1.5, size_box);
}

void graphUIBox::update(){
    
    int ran = ofRandom(1.0, 150.0);
    if(ofGetFrameNum() % ran == 0){
        d = ofRandom(-2.0, 2.0);
    }
    gViewer.pushData(d);
    
    if((size_box >= GRAPHUI_MAX_SIZE && mode_size == 1) || (size_box <= GRAPHUI_MIN_SIZE && mode_size == 2)){
        fix_size_box = 0;
        mode_size = 0;
    }

    size_box += fix_size_box;
    gViewer.setSize(size_box * 1.5, size_box);

}

void graphUIBox::setModesize(int mode_size_){
    mode_size = mode_size_;
    switch(mode_size){
        case 1:
            fix_size_box = 20;
            break;
        case 2:
            fix_size_box = -20;
            break;
        }
}

void graphUIBox::draw(){
    ofPushStyle();
    ofPushMatrix();
    
    ofRotate(25, -0.3, 0.5, 0);
    gViewer.draw(pos.x,pos.y);
    
    ofPopStyle();
    ofPopMatrix();
}