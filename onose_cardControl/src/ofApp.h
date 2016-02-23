#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"


using namespace cv;
using namespace ofxCv;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // ウェブカメラ
    ofVideoGrabber vidGrabber;
    ofxCvColorImage colorImg;
    CvMat colorCvImg;
    
    const int camWidth = 640;
    const int camHeight = 480;
    
    // テンプレート画像
    
    string subjectImgFileName = "card_lit.png";
    ofImage subjectImgFile;
    ofxCvColorImage subjectImg;
    CvMat subjectCvImg;
    
    const int subjectImgWidth = 320;
    const int subjectImgHeight = 240;
    ofPoint subjectImgLoc;
    
    // マッチしたポイント
    CvMat result;
    double minVal, maxVal;
    CvPoint minLoc, maxLoc;
    
    
    
};
