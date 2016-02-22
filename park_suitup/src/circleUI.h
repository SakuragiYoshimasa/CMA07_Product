#include "ofMain.h"

#define NUM_IMAGE 4

class circleUI {
private:
    ofColor color;
    ofPoint pos;
    int size;
    
public:
    void init();
    void updateUI();
    void draw();
    
    ofImage circleImage[NUM_IMAGE];
    float angleCircle[NUM_IMAGE];
    float fix_angle;
};