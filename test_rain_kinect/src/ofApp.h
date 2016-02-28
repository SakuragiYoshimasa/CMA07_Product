#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxOpenNI.h"
#include "Drop.hpp"
#include "Bounce.hpp"

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
  //  Joint JOINT_HEAD;
    
    vector<Drop> rain;
    deque<Bounce> bounces;
    
    ofSoundPlayer soundplayer;
    ofColor jointHue;
    ofColor betweenJointHue;
    ofVec2f circlePosition[100];
    
    float limbVector[10]; //joint間の円の位置
    float rotateVector[10]; //joint間の円の幅
    
    float *volume;
    float Ratio = 1.6; //screenの倍率
    
    
};

