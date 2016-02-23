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
    
    
    string cardFileName = "card_lit.png";
    ofImage ofCardImg;
    ofxCvColorImage ofxCvCardImg;
    
    ofVideoGrabber vidGrabber;
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImg;
//    ofxCvGrayscaleImage featureDetectorMonitor;
    
    Mat grabberImg;
    
    const int camWidth = 640;
    const int camHeight = 480;
    
    // feature detection
    Mat imgScene;
    Mat imgCard;
    
    Mat img_matches;
    
    
    vector<DMatch> matches;
};
