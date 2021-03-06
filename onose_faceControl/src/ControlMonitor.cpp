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

void ControlMonitor::draw(FaceTracker& faceTracker){
//    faceTracker = faceTrackerRef;
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
    if (faceTracker.getFound()) {
        drawControlCircle(faceTracker);
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
    
    drawSoundWaveCircle(faceTracker);
    
}

void ControlMonitor::drawSoundWaveCircle(FaceTracker& faceTracker){
    float r = 45.0;
    float w = 0.5;
    float barBase = 3.0;
    float barMult = 7.0;
    float barRotateSpeed = 0.1;
    ofFill();
    ofSetColor(0, 255, 255);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    ofPushMatrix();
    
    ofRotateZ(time * barRotateSpeed);
    for (int i = 0; i < bufferSize; i++) {
        ofRotateZ(360.0 / bufferSize);
        // 線の長さ
        float l = barBase + buffer[i] * barMult;
        ofRect(-(w / 2.0), r - (l / 2.0), w, l);
    }
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofSetLineWidth(2);
    
    ofCircle(0, 0, r * 0.8);
    
    ofPopMatrix();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


