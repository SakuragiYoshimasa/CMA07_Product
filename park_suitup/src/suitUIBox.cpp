#include "suitUIBox.h"

void suitUIBox::init(float x, float y, int size){
    pos.x = x;
    pos.y = y;
    size_box = size;
    
    d = 0;
    
    gViewer.setup(512);
    gViewer.setRange(-2.0, 2.0);
    gViewer.setSize(512, 200);
}

void suitUIBox::updateUI(){

    int ran = ofRandom(1.0, 150.0);
    if(ofGetFrameNum() % ran == 0){
        d = ofRandom(-2.0, 2.0);
    }
    gViewer.pushData(d);
}

void suitUIBox::draw(){
    gViewer.draw(pos.x,pos.y);
}