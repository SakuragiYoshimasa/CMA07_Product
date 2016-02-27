#include "graphUIBox.h"


void graphUIBox::init(ofPoint pos_, char mode_pos_){
    pos = pos_;
    mode_pos = mode_pos_;
    
    size_box = GRAPHUI_MAX_SIZE/2;
    fix_size_box = 0;
    mode_size = 0;
    
    d = 0;
    
    gViewer.setup(512);
    gViewer.setRange(-2.0, 2.0);
    gViewer.setSize(size_box * 1.5, size_box);
    
    //setup blur
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    s.maxFilter = GL_LINEAR; GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = false;
    s.useStencil = false;
    
    gpuBlur.setup(s, false);
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
    switch (mode_pos) {
        case 't':
            pos.x -= fix_size_box/10;
            pos.y += fix_size_box/10;
            break;
        case 'b':
            pos.x -= fix_size_box/10;
            pos.y -= fix_size_box/10;
            break;
    }

    
    gViewer.setSize(size_box * 1.5, size_box);
    
    //update blur
    gpuBlur.blurOffset = 100 * ofMap(ofGetMouseY(), 0, ofGetHeight(), 1, 0, true);
    //gpuBlur.blurOffset = 15;
    gpuBlur.blurPasses = 50 * ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 1, true);
    //gpuBlur.blurPasses = 1;
    gpuBlur.numBlurOverlays = 1;
    gpuBlur.blurOverlayGain = 255;
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

    ofTranslate(pos);
    
    switch (mode_pos) {
        case 't':
            ofRotate(GRAPHUI_ANGLE, 0.3, 0.5, 0);
            break;
        case 'b':
            ofRotate(GRAPHUI_ANGLE, -0.3, 0.5, 0);
            break;
    }

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    gpuBlur.beginDrawScene();
        ofClear(0, 0, 0, 0);
        ofSetColor(255);
        gViewer.draw(pos.x/2,pos.y/2);
    gpuBlur.endDrawScene();
    
    //blur the fbo
    //blending will be disabled at this stage
    gpuBlur.performBlur();
    
    //overlay the blur on top
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
    gpuBlur.drawBlurFbo();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    
    ofPopStyle();
    ofPopMatrix();
}