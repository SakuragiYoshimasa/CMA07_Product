#include <stdio.h>
#include <particleScene.h>

particleScene::particleScene(){

}

void particleScene::reset(){
    
    pos.x = ofRandomWidth();
    pos.y = ofRandomHeight();
    
    vel.x = ofRandom(-10.0, 10.0);
    vel.y = ofRandom(-10.0, 10.0);
    
    scale = ofRandom(0.5, 1.0);
}


void particleScene::update(ofPoint facePosition){
    
    //updatePosition
    pos += vel;
    
    //settingArea
    if( pos.x > ofGetWidth() ){
        pos.x = ofGetWidth();
        vel.x *= -1.0;
    }else if( pos.x < 0 ){
        pos.x = 0;
        vel.x *= -1.0;
    }
    if( pos.y > ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if( pos.y < 0 ){
        pos.y = 0;
        vel.y *= -1.0;
    }
}

void particleScene::draw(ofVideoPlayer video){
    unsigned char * pixels = video.getPixels();
    
    unsigned char color;
    switch((int)ofRandom(1,3)){
        case 1:
            color = pixels[((int)pos.y) * ((int)video.getWidth()) * 3 + ((int)pos.x) * 3];
            ofSetColor((float)color, 0, 0);
            break;
        case 2:
            color = pixels[((int)pos.y) * ((int)video.getWidth()) * 3 + ((int)pos.x) * 3+1];
            ofSetColor(0, (float)color, 0);
            break;
        case 3:
            color = pixels[((int)pos.y) * ((int)video.getWidth()) * 3 + ((int)pos.x) * 3+2];
            ofSetColor(0, 0, (float)color);
            break;
    }

    ofDrawCircle(pos.x, pos.y, scale * (40.0 * (float)color/255));
}

