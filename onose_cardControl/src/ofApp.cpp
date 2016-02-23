#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    // カメラを設定
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    colorImg.allocate(camWidth, camHeight);
//    colorCvImg = toCv(vidGrabber.getPixelsRef());
    
    // テンプレート画像を定義
    subjectImgFile.loadImage(subjectImgFileName);
    subjectImgFile.resize(subjectImgWidth, subjectImgHeight);
    subjectImg.setFromPixels(subjectImgFile.getPixels(), subjectImgWidth, subjectImgHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //-- カメラを更新
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        colorImg.setFromPixels(vidGrabber.getPixels(), camWidth, camHeight);
    }
    
    
    //-- テンプレートマッチング
    // result の領域を確保
    IplImage *result = cvCreateImage(cvSize(camWidth - subjectImgWidth + 1, camHeight - subjectImgHeight + 1), 32, 1);
    cvMatchTemplate(colorImg.getCvImage(), subjectImg.getCvImage(), result, CV_TM_SQDIFF);
    
    // 結果を取得
    cvMinMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, 0);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // カメラフレームを描画
    ofSetHexColor(0xffffff);
    colorImg.draw(0, 0);
    
    // テンプレート画像を表示
    subjectImg.draw(camWidth, 0, subjectImgWidth, subjectImgHeight);
    
    // マッチング箇所を表示
    ofNoFill();
    ofSetHexColor(0x00ffff);
    ofRect(minLoc.x, minLoc.y, subjectImgWidth, subjectImgHeight);
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
