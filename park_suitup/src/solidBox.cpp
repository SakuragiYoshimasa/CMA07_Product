
#include "solidBox.h"

void solidBox::init(){
    ofMesh mesh;
    
    char c[] = "011111101001111110100101110010000100"
    "010011001000010110111011000100101001";

    for (int i=0,x,y,z; i<72; i+=3) {
        
        x = c[i+0]-'0';
        y = c[i+1]-'0';
        z = c[i+2]-'0';
        
        mesh.addColor(ofFloatColor(x,y,z));
        mesh.addVertex(ofVec3f(x*2-1,y*2-1,z*2-1));
    }
    
    vbo.setMesh(mesh, GL_STATIC_DRAW);
}

void solidBox::draw(ofQuaternion q, int size_spect, int mode){

    
    ofPushStyle();
    ofPushMatrix();
    ofNoFill();
    glEnable(GL_DEPTH_TEST);
    
    switch(mode){
    case 0:
        ofBackground(0);
        break;
    case 1:
        ofBackground(255);
        break;
    }


    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofMultMatrix(q);

    ofScale(150 + (size_spect%50), 150 + (size_spect%50), 150 + (size_spect%50));
    vbo.draw(GL_QUAD_STRIP,0,24);

    ofPopMatrix();
    ofPopStyle();
    
    
    switch(mode){
        case 0:
            ofPushStyle();
            ofPushMatrix();
            ofNoFill();
            
            ofTranslate(100, 100);
            ofScale(10 + (size_spect%20), 10 +  (size_spect%20), 10 + (size_spect%20));
            vbo.draw(GL_QUAD_STRIP,0,24);
            
            ofPopMatrix();
            ofPopStyle();
            
            ofPushStyle();
            ofPushMatrix();
            ofNoFill();
            
            ofTranslate(ofGetWidth() - 100, ofGetHeight() - 100);
            ofScale(50 + (size_spect%20), 50 +  (size_spect%20), 50 + (size_spect%20));
            vbo.draw(GL_QUAD_STRIP,0,24);
            
            ofPopMatrix();
            ofPopStyle();
            break;
        case 1:
            ofPushStyle();
            ofPushMatrix();
            ofNoFill();
            
            ofTranslate(100, ofGetHeight() - 100);
            ofScale(10 + (size_spect%20), 10 +  (size_spect%20), 10 + (size_spect%20));
            vbo.draw(GL_QUAD_STRIP,0,24);
            
            ofPopMatrix();
            ofPopStyle();
            
            ofPushStyle();
            ofPushMatrix();
            ofNoFill();
            
            ofTranslate(ofGetWidth() - 100, 100);
            ofScale(50 + (size_spect%20), 50 +  (size_spect%20), 50 + (size_spect%20));
            vbo.draw(GL_QUAD_STRIP,0,24);
            
            ofPopMatrix();
            ofPopStyle();
            break;
    }

    glDisable(GL_DEPTH_TEST);

}

void solidBox::update(){
}