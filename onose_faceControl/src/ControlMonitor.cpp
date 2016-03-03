//
//  ControlMonitor.cpp
//  onose_faceControl
//
//  Created by Ryosuke ONOSE on 2/25/16.
//
//

#include "ControlMonitor.h"

ControlMonitor::ControlMonitor(){
    
}

void ControlMonitor::setup(){
}

void ControlMonitor::update(){
    time += 1;
}

void ControlMonitor::keyPressed(int key){
    switch (key) {
        case 'f':
            fToggle *= -1;
            break;
        case 'b':
            bToggle *= -1;
            break;
        case 'l':
            lineToggle *= -1;
            break;
        default:
            break;
    }
}

void ControlMonitor::drawBackgroundMesh(FaceTracker& faceTracker){
    int l = 48;
    ofSetColor(64);
    ofSetLineWidth(1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    ofPushMatrix();
    ofTranslate(conf.camWidth/2, conf.camHeight/2, buffer[0]*100);
    applyMatrix(faceTracker.rotationMatrix);
    for (int k = 0; k < 3; k++) {
        ofRotateZ(60);
        for (int i = 0; i < conf.camHeight*3 / l; i++) {
            ofLine(-conf.camWidth, i*l - conf.camHeight,
                   conf.camWidth*2, i*l - conf.camHeight);
        }
    }
    ofPopMatrix();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ControlMonitor::drawBackground(FaceTracker& faceTracker){
    if(bToggle > 0){
        ofFill();
        ofSetColor(32);
        ofRect(0, 0, conf.camWidth, conf.camHeight);
        if (lineToggle > 0) {
            drawBackgroundMesh(faceTracker);
        }
    }
}

void ControlMonitor::draw(FaceTracker& faceTracker){
//    faceTracker = faceTrackerRef;
    ofSetColor(255);
    faceTracker.drawCam();
    drawBackground(faceTracker);
    ofDrawBitmapString("FPS: " + ofToString((int) ofGetFrameRate()), 10, 20);
    
    
    
    // easyCam.begin();
    ofPushMatrix();
    ofSetupScreenOrtho(conf.camWidth, conf.camHeight, -1000, 1000);
    // 顔の位置に平行移動
    ofTranslate(faceTracker.position.x, faceTracker.position.y);
    // 顔の向きに回転
    applyMatrix(faceTracker.rotationMatrix);
    // 顔の距離に合わせて大きさを変更
    ofScale(faceTracker.scale, faceTracker.scale, faceTracker.scale);
    // コントロールサークルを描画
    if (faceTracker.getFound()) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        if(fToggle > 0){
            ofSetColor(126);
            faceTracker.drawFaceWire();
        }
        drawControlCircle(faceTracker);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    ofPopMatrix();
    // easyCam.end();
}

void ControlMonitor::drawControlCircle(FaceTracker& faceTracker){
    ofNoFill();
    if(faceTracker.getFound()){
        ofColor hue;
        hue.setHsb(ofMap(faceTracker.orientation.z, -conf.faceOriZThreshold, conf.faceOriZThreshold, 0, 360), 255, 255);
        ofSetColor(hue);
    }
    
    ofTranslate(0, 0, 5);
    drawSoundWaveCircle(faceTracker);
    ofTranslate(0, 0, -15);
    drawCircleMonitor(ofMap(faceTracker.orientation.z, -conf.faceOriZThreshold, conf.faceOriZThreshold, -180, 180), "Z");
    drawCrescentMonitor(ofMap(faceTracker.orientation.x, -conf.faceOriXThreshold, conf.faceOriXThreshold, -180, 180), "X");
    ofRotate(-90);
    drawCrescentMonitor(ofMap(faceTracker.orientation.y, -conf.faceOriYThreshold, conf.faceOriYThreshold, 180, -180), "Y");
}

void ControlMonitor::drawCrescentMonitor(float angle, string label){
    float r = 40.0;
    float w = 2.0;
    float l = 3.0;
    float crescentDeg = 60;
    int numBin = 16;
    
    ofPushMatrix();
    ofRotate(-crescentDeg / 2.0);
    ofSetColor(255);
    ofDrawBitmapString(label, r, 0);
    ofSetColor(255, 0, 0);
    for (int i = 0; i < numBin; i++) {
        ofRotate(crescentDeg / numBin);
        int idx = ofMap(angle, -180, 180, 0, numBin);
        if(i < numBin/2 && i > idx){
            ofFill();
        }else if(i > numBin/2 && i < idx){
            ofFill();
        }else{
            ofNoFill();
        }
        ofRect(r - w/2.0, -l/2.0, l, w);
    }
    
    ofPopMatrix();
}

void ControlMonitor::drawCircleMonitor(float angle, string label){
    float r = 45.0;
    float l = 2.0;
    float w = 5.0;
    
    ofPushMatrix();
    ofRotate(-90);
    ofSetColor(255);
    ofDrawBitmapString(label, r, 0);
    ofSetColor(255, 0, 0);
    ofFill();
    for (int i = 0; i < 360; i++) {
        ofRotateZ(1);
        if(i < angle && angle > 0){
            ofRect(r - w/2.0, -l/2.0, l, w);
        }if(i > angle+360 && angle < 0){
            ofRect(r - w/2.0, -l/2.0, l, w);
        }else{
            ofRect(r - w/2.0, -l/6.0, l/3.0, w);
        }
        
    }
    ofPopMatrix();
}

void ControlMonitor::drawSoundWaveCircle(FaceTracker& faceTracker){
    float r = 45.0;
    float w = 0.5;
    float barBase = 2.0;
    float barMult = 10.0;
    float barRotateSpeed = 0.1;
    
    ofPushMatrix();
    // 少しずつ回転
    ofRotateZ(time * barRotateSpeed);
    ofFill();
    for (int i = 0; i < bufferSize; i++) {
        //
        ofRotateZ(360.0 / bufferSize);
        // 音域を印字
        ofSetColor(255);
        if(i == bufferSize*1/9) ofDrawBitmapString("LOW", r + barMult, 0);
        if(i == bufferSize/2) ofDrawBitmapString("MID", r + barMult, 0);
        if(i == bufferSize*8/9) ofDrawBitmapString("HIGH", r + barMult, 0);
        // 音の可視化
        if(faceTracker.getMouseOpend()){
            ofColor waveColor;
            waveColor.setHsb((int(buffer[i] * 10000) % 360), 255, 126);
            ofSetColor(waveColor);
        }else{
            ofSetColor(0, 255, 255);
        }
        
        float l = barBase + buffer[i] * barMult;
        ofRect(-(w / 2.0), r, w, l);
    }
    ofPopMatrix();
}


