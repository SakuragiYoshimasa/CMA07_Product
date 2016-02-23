#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxOpenNI.h"
#include "Drop.hpp"

class ofApp : public ofBaseApp{
    
    //ofxOpenNI
private:
    ofxOpenNI kinect;
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    Limb need_limb_id[6] = {LIMB_LEFT_LOWER_ARM,LIMB_LEFT_UPPER_ARM,LIMB_RIGHT_LOWER_ARM,LIMB_RIGHT_UPPER_ARM,LIMB_RIGHT_SHOULDER,LIMB_LEFT_SHOULDER};
    
    vector<Drop> rain;
};

