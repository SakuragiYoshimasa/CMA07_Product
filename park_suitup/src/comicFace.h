#include "ofMain.h"
#include "ofxFaceTracker.h"

class comicFace{
public:
    void init();
    void draw(ofxFaceTracker & tracker);
    
    ofImage noseImage;
    ofImage mouseImage;
    ofImage leftEyeImage;
    ofImage rightEyeImage;

};
