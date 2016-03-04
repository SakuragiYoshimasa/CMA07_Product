#include "dotMovie.h"


void dotMovie::update(){

}

void dotMovie::draw(ofVideoPlayer video){
 
    unsigned char * pixels = video.getPixels();
    
    for (int i = 0; i < video.getWidth(); i+=4){
        for (int j = 0; j < video.getHeight(); j+=4){
            
            unsigned char r = pixels[j * ((int)video.getWidth()) * 3 + i * 3];
            unsigned char g = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 1];
            unsigned char b = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 2];
            
            ofSetColor(255, 0, 0, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)r/255.0));
            ofSetColor(0, 255, 0, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)g/255.0));
            ofSetColor(0, 0, 255, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)b/255.0));
        }
    }
}

void dotMovie::draw(ofVideoPlayer video, char mode, int size_spect){
    
    unsigned char * pixels = video.getPixels();
    
    for (int i = 0; i < video.getWidth(); i+=4){
        for (int j = 0; j < video.getHeight(); j+=4){
            
            unsigned char r = pixels[j * ((int)video.getWidth()) * 3 + i * 3];
            unsigned char g = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 1];
            unsigned char b = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 2];
            
            switch (mode) {
                case 'r':
                    ofSetColor(255, 0, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)r/255.0) * size_spect);
                    break;
                case 'g':
                    ofSetColor(0, 255, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)g/255.0) * size_spect);
                    break;
                case 'b':
                    ofSetColor(0, 0, 255, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)b/255.0) * size_spect);
                    break;
            }
        }
    }
}

void dotMovie::draw(ofVideoPlayer video, char mode, int size_spect1, int size_spect2){
    
    unsigned char * pixels = video.getPixels();
    
    for (int i = 0; i < video.getWidth(); i+=4){
        for (int j = 0; j < video.getHeight(); j+=4){
            
            unsigned char r = pixels[j * ((int)video.getWidth()) * 3 + i * 3];
            unsigned char g = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 1];
            unsigned char b = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 2];
            
            switch (mode) {
                case 'y':
                    ofSetColor(255, 0, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)r/255.0) * size_spect1);
                    ofSetColor(0, 255, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)g/255.0) * size_spect2);
                    break;
                case 'p':
                    ofSetColor(255, 0, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)r/255.0) * size_spect1);
                    ofSetColor(0, 0, 255, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)b/255.0) * size_spect2);
                    break;
                    break;
                case 'c':
                    ofSetColor(0, 255, 0, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)g/255.0) * size_spect1);
                    ofSetColor(0, 0, 255, 50);
                    ofDrawCircle(i,30 + j,(10.0*(float)b/255.0) * size_spect2);
                    break;
            }
        }
    }
}


void dotMovie::draw(ofVideoPlayer video, int size_spect1, int size_spect2, int size_spect3){
    
    unsigned char * pixels = video.getPixels();
    
    for (int i = 0; i < video.getWidth(); i+=4){
        for (int j = 0; j < video.getHeight(); j+=4){
            
            unsigned char r = pixels[j * ((int)video.getWidth()) * 3 + i * 3];
            unsigned char g = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 1];
            unsigned char b = pixels[j * ((int)video.getWidth()) * 3 + i * 3 + 2];
            
            ofSetColor(255, 0, 0, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)r/255.0) * size_spect1);
            ofSetColor(0, 255, 0, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)g/255.0) * size_spect2);
            ofSetColor(0, 0, 255, 50);
            ofDrawCircle(i,30 + j,(10.0*(float)b/255.0) * size_spect3);
        }
    }
}