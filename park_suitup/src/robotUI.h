#include "ofMain.h"
#include "ofxOpenCv.h"


#define NUM_IMAGE 4

class robotUI {
private:
    ofPoint pos;
    int size;
    
public:
    void init(ofPoint pos_);
    void update();
    void draw();
    
    ofImage robotImage[NUM_IMAGE];
};