#include "ofMain.h"

#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

#define NUM_IMAGE 4
#define CIRCLE_MAX_Z 50

class circleUI {
private:
    ofColor color;
    int size;
    
public:
    void init();
    void update(int size_spect[]);
    void draw();
    
    ofImage circleImage[NUM_IMAGE];
    float angleCircle[NUM_IMAGE];
    float fix_angle;
    int sizeCircle[NUM_IMAGE];
    
    ofxAnimatableFloat  anim;
};