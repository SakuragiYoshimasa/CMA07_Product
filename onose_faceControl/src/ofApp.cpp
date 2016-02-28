#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // サウンドセットアップ
    controlMonitor.bufferSize = 0;
    ofSoundStreamSetup(0, 1, this, 44100, BUFSIZE, 4);
    
    // 
    midiControl.setup();
    faceTracker.setup();
    controlMonitor.setup();
    
}


void ofApp::update() {
    // サウンド
    fft = ofSoundGetSpectrum(nBandsToGet); // FFT 解析
    // クラスのアップデート
    midiControl.update(); // midiControl のアップデート
    faceTracker.update(); // faceTracker のアップデート
    controlMonitor.update(); // モニタをアップデート
    // 顔の向きから Midi 出力 x: 16, y: 17, z: 18
    midiControl.faceOriControl(faceTracker);
}

void ofApp::draw() {
    controlMonitor.draw(faceTracker);
//    midiControl.viewIndicator();
    
    
}

void ofApp::keyPressed(int key) {
    
    switch (key) {
        case ' ':
//            midiControl.controlWave(16, 0.01);
            break;
        case 'r':
            break;
        default:
            break;
    }
}
void ofApp::mouseDragged(int x, int y, int button){
    midiControl.mouseDragged(x, y, button);
}

void ofApp::exit(){
    midiControl.exit();
}

void ofApp::audioReceived (float *buf, int bufSize, int nChan) {
    controlMonitor.bufferSize = bufSize;
    for (int i = 0; i < controlMonitor.bufferSize; i++)
        controlMonitor.buffer[i] = buf[i];
}