
#include "ofMain.h"

#define NUM_BOX 3

class solidBox{
public:
    void init();
    void draw(ofQuaternion q, int size_spect);
    void update();
    
    ofVbo vbo;
    ofEasyCam camera;
    
    int scaleBox;
    float dregessBox;
};

