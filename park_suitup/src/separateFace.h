
#include "ofMain.h"
#include "ofxOpenCv.h"

class separateFace{
public:
    void update();
    void draw(ofPixels & cam, ofPoint facePoint, ofPoint mousePoint, ofPoint leftEyePoint, ofPoint rightEyePoint, int mode);
    
    //for cutImage
    ofxCvColorImage colorImg;
    ofImage grayImg;
};