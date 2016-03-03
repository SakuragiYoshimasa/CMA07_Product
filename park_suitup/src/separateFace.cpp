#include "separateFace.h"

void separateFace::draw(ofPixels & cam, ofPoint facePoint, ofPoint mousePoint, ofPoint leftEyePoint, ofPoint rightEyePoint){
    
    colorImg.allocate(ofGetWidth(),ofGetHeight());
    colorImg.setFromPixels(cam, ofGetWidth(), ofGetHeight());
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(facePoint/2);
    ofRotate( 180, 0, 0, 1 );

    //draw leftEye
    colorImg.setROI(leftEyePoint.x-50, leftEyePoint.y-50, 100, 100);
    colorImg.drawROI(-leftEyePoint.x, -leftEyePoint.y);
    colorImg.resetROI();
    
    //draw rightEye
    colorImg.setROI(rightEyePoint.x-50, rightEyePoint.y-50, 100, 100);
    grayImg = colorImg.getRoiPixels();
    grayImg.setImageType(OF_IMAGE_GRAYSCALE);
    grayImg.draw(-rightEyePoint.x, -rightEyePoint.y);
    colorImg.resetROI();
    
    //drawMouse
    colorImg.setROI(mousePoint.x-100, mousePoint.y-50, 200, 100);
    grayImg = colorImg.getRoiPixels();
    grayImg.setImageType(OF_IMAGE_GRAYSCALE);
    grayImg.draw(-mousePoint.x, -mousePoint.y);
    colorImg.resetROI();
    
    ofPopMatrix();
    ofPopStyle();
}
