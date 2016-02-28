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
    
}

void ControlMonitor::draw(FaceTracker& faceTracker){
    ofSetColor(255);
    faceTracker.drawCam();
    ofDrawBitmapString("FPS: " + ofToString((int) ofGetFrameRate()), 10, 20);
//    faceTracker.drawTracker();
    
    
    // easyCam.begin();
    ofPushMatrix();
    ofSetupScreenOrtho(conf.camWidth, conf.camHeight, -1000, 1000);
    // 顔の位置に平行移動
    ofTranslate(faceTracker.position.x, faceTracker.position.y - faceTracker.scale * 8);
    // 顔の向きに回転
    applyMatrix(faceTracker.rotationMatrix);
    // 顔の距離に合わせて大きさを変更
    ofScale(faceTracker.scale, faceTracker.scale, faceTracker.scale);
    // コントロールサークルを描画
    drawControlCircle(faceTracker);
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
    ofCircle(0, 0, 0, 30);
//    if(faceTracker.getMouseOpend()){
//        centerSphere.set(10, 10);
//        centerSphere.drawWireframe();
//    }
    ofFill();
//    ofRect(30, -6, ofMap(faceTracker.orientation.x, -conf.faceOriXThreshold, conf.faceOriXThreshold, -25, 25), 4);
//    ofRect(30, 0, ofMap(faceTracker.orientation.y, -conf.faceOriYThreshold, conf.faceOriYThreshold, -50, 50), 4);
//    ofRect(30, 6, ofMap(faceTracker.orientation.z, -conf.faceOriZThreshold, conf.faceOriZThreshold, -50, 50), 4);
    ofNoFill();
//    ofRect(5, -6, 50, 4);
//    ofDrawBitmapString("x: " + ofToString(faceTracker.orientation.x), 20, 20);
//    ofDrawBitmapString("y: " + ofToString(faceTracker.orientation.y), 20, 26);
//    ofDrawBitmapString("z: " + ofToString(faceTracker.orientation.z), 20, 32);
//    ofDrawBitmapString("mouth: " + ofToString(faceTracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT)), 20, 38);
    
    drawSoundWaveCircle();
    
}

void ControlMonitor::drawSoundWaveCircle(){
    for (int i = 0; i < bufferSize; i++) {
        int dy = buffer[i] * 20;
        ofSetLineWidth(2);
        ofLine(-i, 10, -i, 10 - dy);
    }
    
}


