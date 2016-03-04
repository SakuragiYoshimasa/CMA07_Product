#include "comicFace.h"


void comicFace::init(){
    noseImage.load("image/nose.png");
    mouseImage.load("image/mouse.png");
    leftEyeImage.load("image/lefteye.png");
    rightEyeImage.load("image/righteye.png");
}

void comicFace::draw(ofxFaceTracker & tracker){
    
//    ofPoint nosePoint, ofPoint mousePoint, ofPoint leftEyePoint, ofPoint rightEyePoint
    ofPoint nosePoint = (tracker.getImagePoint(27)+tracker.getImagePoint(30))/2;
    ofPoint mousePoint = (tracker.getImagePoint(48)+tracker.getImagePoint(54))/2;
    
    float mouseWidth = (float) ofDist(tracker.getImagePoint(54).x, tracker.getImagePoint(54).y, tracker.getImagePoint(48).x, tracker.getImagePoint(48).y);
    float mouseHeight = (float) ofDist(tracker.getImagePoint(57).x, tracker.getImagePoint(57).y, tracker.getImagePoint(51).x, tracker.getImagePoint(51).y);
    
    ofPoint leftEyePoint = (tracker.getImagePoint(36)+tracker.getImagePoint(39))/2;
    ofPoint rightEyePoint = (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2;
    
    ofBackground(255);
    noseImage.setAnchorPercent(0.5, 0.5);
    noseImage.draw(nosePoint);
    
    mouseImage.setAnchorPercent(0.5, 0.5);
    mouseImage.draw(mousePoint,mouseWidth,mouseHeight);
    
    leftEyeImage.setAnchorPercent(0.5, 0.5);
    leftEyeImage.draw(leftEyePoint);
    
    rightEyeImage.setAnchorPercent(0.5, 0.5);
    rightEyeImage.draw(rightEyePoint);
}