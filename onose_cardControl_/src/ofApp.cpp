#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetBackgroundColor(0);
//    grabber.initGrabber(960, 640);
    
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    colorImg.allocate(camWidth, camHeight);
//    grayImg.allocate(camWidth, camHeight);
    
    // load card image
    ofCardImg.loadImage(cardFileName);
    ofCardImg.resize(320, 240);
    ofxCvCardImg.setFromPixels(ofCardImg.getPixels(), 320, 240);
    imgCard = ofxCvCardImg.getCvImage();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
//    vidGrabber.getPixelFormat();
//    if (vidGrabber.isFrameNew())
//    {
//        colorImg.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);
//    }
    colorImg.setFromPixels(vidGrabber.getPixels(), camWidth,camHeight);

//    grabberImg = vidGrabber.getPixelFormat();
//    copyGray(vidGrabber, grabberImg);
//    
//    SurfFeatureDetector detector;
    
//    copyGray(colorImg, grayImg);
    grayImg = colorImg;
    
    //// feature detection
    
    imgScene = grayImg.getCvImage();
    
    // 1. detecting keypoints
    
    FastFeatureDetector detector(50);
    vector<KeyPoint> keypointsScene;
    detector.detect(imgScene, keypointsScene);
    vector<KeyPoint> keypointsCard;
    detector.detect(imgCard, keypointsCard);
    
    // 2. computing descriptors
    SurfDescriptorExtractor extractor;
    Mat descriptorsScene;
    extractor.compute(imgScene, keypointsScene, descriptorsScene);
    Mat descriptorsCard;
    extractor.compute(imgScene, keypointsCard, descriptorsCard);
    
    // 3. matching descriptors
//    BruteForceMatcher<L2<float> > matcher;
//    matcher.match(descriptorsScene, descriptorsCard, matches);
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match(descriptorsScene, descriptorsCard, matches);
    
    double max_dist = 0; double min_dist = 100;
    
    for( int i = 0; i < descriptorsScene.rows; i++ ){
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    
    std::vector<DMatch> good_matches;
    
    for( int i = 0; i < descriptorsScene.rows; i++ ){
        if( matches[i].distance <= max(2*min_dist, 0.02) ){ good_matches.push_back( matches[i]);
        }
    }
    
    drawMatches(imgScene, keypointsScene, imgCard, keypointsCard, good_matches, img_matches, DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    
//    drawKeypoints(imgScene, keypointsScene, img_matches);
    
    // 5. export matching img data
    
//    drawMatches(imgScene, keypointsScene, imgCard, keypointsCard, matches, img_matches);
    ofImage tempImg;
    toOf(img_matches, tempImg);
    colorImg.setFromPixels(tempImg.getPixels(), camWidth, camHeight);
    
    // *.
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    flow.draw();
//    if(ofGetMousePressed()){
//        ofNoFill();
//        ofRect(rect);
//    }
    ofSetHexColor(0xffffff);
//    grayImg.draw(0, 0, camWidth, camHeight);
    colorImg.draw(0, 0, camWidth, camHeight);
    
    vidGrabber.draw(camWidth + 320, 0, -320, 240);
    ofxCvCardImg.draw(camWidth, camHeight/2, camWidth/2, camHeight/2);
    

    matches.size();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case ' ':
            
            break;
        default:
            
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    ofVec2f p2(x,y);
//    rect.set(p1,p2.x-p1.x,p2.y-p1.y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
//	p1.set(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    ofVec2f p2(x,y);
//    rect.set(p1,p2.x-p1.x,p2.y-p1.y);
//    vector<KeyPoint> keypoints;
//    vector<KeyPoint> keypointsInside;
//    vector<cv::Point2f> featuresToTrack;
//    copyGray(grabber, grabberGray);
//    FAST(grabberGray,keypoints,2);
//    for(int i=0;i<keypoints.size();i++){
//        if(rect.inside(toOf(keypoints[i].pt))){
//            keypointsInside.push_back(keypoints[i]);
//        }
//    }
//#if CV_MAJOR_VERSION>=2 && (CV_MINOR_VERSION>4 || (CV_MINOR_VERSION==4 && CV_SUBMINOR_VERSION>=1))
//    KeyPointsFilter::retainBest(keypointsInside,30);
//#endif
//    KeyPoint::convert(keypointsInside,featuresToTrack);
//    flow.setFeaturesToTrack(featuresToTrack);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}