#include "ofMain.h"


#define NUM_IMAGE 4
#define NUM_CIRCLE 5

class robotUI {
private:
    ofPoint pos;
    int size;
    int moveCircleZ;
    
public:
    void init(ofPoint pos_);
    void update();
    void draw();
    
    ofImage robotImage[NUM_IMAGE];
};