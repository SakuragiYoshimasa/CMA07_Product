#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    //setupSound
    suitBgmPlayer.load("sound/ironmanBGM.mp3");
    suitBgmPlayer.setLoop(true);
    suitBgmPlayer.setVolume(1.0);
    suitBgmPlayer.play();
    
    mainBgmPlayer.load("sound/IronManRemix.mp3");
    mainBgmPlayer.setLoop(false);
    mainBgmPlayer.setVolume(1.0);
    
    effectWarningPlayer.load("sound/AlarmAlertEffect.mp3");
    effectWarningPlayer.setLoop(false);
    effectWarningPlayer.setVolume(1.0);

    
    //setup Camera
	cam.initGrabber(1280, 720);
    
    //setup Mask
    maskImg.load("image/mask.jpg");
    bottomImg.load("image/bottomimage.jpg");

    alphaMask = new ofxAlphaMaskTexture(cam.getTexture(),       // top layer texture
                                        bottomImg.getTexture(), // bottom layer texture
                                        maskImg.getTexture());  // mask layer texture
	
    //seup Facetracker
	tracker.setup();
	tracker.setRescale(.5);
    
    //setup UI
    eyeCircle.init();
    
    uibox_b.init(ofPoint(ofGetWidth()/2 + 100, 400),'b');
    uibox_t.init(ofPoint(ofGetWidth()/2 + 100, 10),'t');
    robot.init(ofPoint(40,500));
    
    //setup Shader
    shader.load("shader/chromaKey");
    
    //setup Movie
    openingMovie.load("movie/openingMovie.mp4");
    mainMovie.load("movie/IronManRemix.mp4");
    interfaceMovie.load("movie/interface.mp4");
    
    //setup Particle
    p.assign(MAXNUM_PARTICLE, particleScene());
    
    attractPoints.clear();
    for(int i = 0; i < 4; i++){
        attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
    }
    
    attractPointsWithMovement = attractPoints;
    
    for(unsigned int i = 0; i < p.size(); i++){
        p[i].reset();
    }
    
    //setup Solidbox
    solidbox.init();
    
    //setup comicFace
    comicface.init();
    
    //setup SceneController
    timeTable = {9000.0, 19500.0, 31000.0, 36000.0,40000.0,50000.0,100000.0};
    sceneTable = {IN_SUIT_SCENE, OPENING_START, COMIC_FACE, PARTICLE_COLOR, DOT_MOVIE, SEPARATE_FACE};
    numTimeTable  = 0;
    
    sMode = APP_START;
    
    //start
    openingMovie.play();
}

void ofApp::update() {
    //update Scene

    if(ofGetElapsedTimeMillis() >= timeTable[numTimeTable]){
        sMode = sceneTable[numTimeTable];
        numTimeTable++;
        
        //stopOpeningMovie only once
        if(sMode == IN_SUIT_SCENE){
            openingMovie.close();
            interfaceMovie.play();
        }
        
        //start to paly mainMovie only once
        if(sMode == OPENING_START){
            interfaceMovie.close();
            suitBgmPlayer.stop();
            effectWarningPlayer.stop();
            
            mainMovie.setAnchorPercent(0.5, 0.5);
            mainMovie.play();
            mainBgmPlayer.play();
        }
    }

    //updateSpectrumBar
    for(int i = 0 ; i < NUM_SPECTRUM ; i++){
        float * volume = ofSoundGetSpectrum(i+1);
        size_spect[i] = volume[0] * 1300;
    }
    
    //update Camera
    cam.update();

    switch (sMode) {
        case 0:
            openingMovie.update();
            break;
        case 1:
            if(cam.isFrameNew()) {
                //update UI
                uibox_b.update();
                uibox_t.update();
                robot.update();
                eyeCircle.update(size_spect);
                
                alphaMask->maskScale =  ofMap(tracker.getScale(),0.0,10.0,0.0,1.0);
                ofPixels newPixels = cam.getPixels();
                ofPixels reversePixels;
                reversePixels.allocate(cam.getWidth(), cam.getHeight(), OF_PIXELS_BGR);
                
                //reverse cam pixels
                for(int h = 0; h < cam.getHeight(); h++){
                    for(int w = 0; w < cam.getWidth(); w++){
                        reversePixels[h * cam.getWidth() * 3 + w * 3] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 - w) * 3];
                        reversePixels[h * cam.getWidth() * 3 + w * 3 + 1] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 1];
                        reversePixels[h * cam.getWidth() * 3 + w * 3 + 2] = newPixels[h * cam.getWidth() * 3 + (cam.getWidth() - 1 -w) * 3 + 2];
                    }
                }
                
                if(tracker.update(toCv(reversePixels))) {
                    classifier.classify(tracker);
                }
                
                reversePixels.clear();
                newPixels.clear();
                
                if(tracker.getHaarFound()){
                    ofVec3f angleFace = tracker.getRotationMatrix().getRotate().getEuler();
                    //control_ui_right
                    if(angleFace.y < 0){
                        uibox_b.setModesize(1);
                        uibox_t.setModesize(1);
                    }else if(angleFace.y > 0){
                        uibox_b.setModesize(2);
                        uibox_t.setModesize(2);
                    }
                }
            }
            interfaceMovie.update();
            
            if(ofGetElapsedTimeMillis() >= 17500.0){
                effectWarningPlayer.play();
            }
            break;
        case 2:
            mainMovie.update();
            break;
        case 3:
            mainMovie.update();
            break;
            
        case 4:
            if(tracker.update(toCv(cam))) {
                classifier.classify(tracker);
            }
            mainMovie.update();
            break;
            
        case 5:
            if(tracker.update(toCv(cam))) {
                classifier.classify(tracker);
            }
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].update(tracker.getPosition());
            }
            
            //lets add a bit of movement to the attract points
            for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
                attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
                attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
            }
            
            mainMovie.update();
            break;
            
        case 6:
            if(tracker.update(toCv(cam))) {
                classifier.classify(tracker);
            }
            mainMovie.update();
            break;
        case 7:
            if(tracker.update(toCv(cam))) {
                classifier.classify(tracker);
            }
            mainMovie.update();
            break;
//        default:
//            if(tracker.update(toCv(cam))) {
//                classifier.classify(tracker);
//            }
//            break;
    }
}

void ofApp::draw() {
	ofSetColor(255);
    
//    cam.draw(cam.getWidth(), 0, -cam.getWidth(), cam.getHeight());
    

    
    switch(sMode){
        case 0:
            openingMovie.draw(0, 0);
            break;
        case 1:
            ofBackground(255);
            ofPushStyle();
            ofPushMatrix();
            
            ofScale(-1,1);
            ofTranslate(-cam.getWidth(),0);
            alphaMask->draw();
            
            ofPopMatrix();
            ofPopStyle();
            
            shader.begin();
            shader.setUniform3f("chromaKeyColor", ofVec3f(0.0, 0.0, 0.0));
            shader.setUniform1f("difference", 0.239);
            interfaceMovie.draw(0,0);
            shader.end();
            
            if(tracker.getHaarFound()){
                
                if(tracker.getImagePoint(42) != tracker.getImagePoint(45)){
                    //draw movalbe UI
                    ofPushStyle();
                    ofPushMatrix();
                    ofPoint eyePos = (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2;
                    ofTranslate(eyePos);
                    
                    //reverseMatrix
                    ofMatrix4x4 reverseMatrix;
                    ofQuaternion newMatrix = tracker.getRotationMatrix().getRotate();
                    
                    newMatrix.set(-newMatrix.x(), -newMatrix.y(), newMatrix.z(), newMatrix.w());
                    reverseMatrix.setRotate(newMatrix);
                    ofMultMatrix(reverseMatrix);
                    
                    eyeCircle.draw();
                    
                    ofPopMatrix();
                    ofPopStyle();
                }
                //draw stand UI
                ofPushStyle();
                ofPushMatrix();
                
                //lineGraph
                uibox_b.draw();
                uibox_t.draw();
                robot.draw();
                
                tracker.getImageFeature(tracker.FACE_OUTLINE).draw();
                
                ofPopMatrix();
                ofPopStyle();
            }
            break;
            
        case 2:
            ofBackground(0);
            mainMovie.draw(ofGetWidth()/2,ofGetHeight()/2);
            break;
            
        case 3:
            ofBackground(255);
            dotmovie.draw(mainMovie);
            break;
            
        case 4:
            ofBackground(255);
            separateface.draw(cam.getPixels(), tracker.getPosition(), (tracker.getImagePoint(48)+tracker.getImagePoint(54))/2,
                              (tracker.getImagePoint(36)+tracker.getImagePoint(39))/2, (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2);
            separateface.draw(cam.getPixels(), -tracker.getPosition(), (tracker.getImagePoint(48)+tracker.getImagePoint(54))/2,
                              (tracker.getImagePoint(36)+tracker.getImagePoint(39))/2, (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2);
            break;
            
        case 5:
            ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
            
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].draw(mainMovie);
            }
            break;
        case 6:
            solidbox.draw(tracker.getRotationMatrix().getRotate(), size_spect[3]);
            break;
        case 7:
            comicface.draw(tracker);
            break;
    }

	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis()), ofGetWidth()/2, ofGetHeight() - 50);
    ofDrawBitmapString(ofToString(sMode), ofGetWidth()/2, ofGetHeight() - 20);
}

void ofApp::keyPressed(int key) {
    switch(key){
        case 'r'    :
            tracker.reset();
            classifier.reset();
            break;
        case 'e'    :
            classifier.addExpression();
            break;
        case 'a'    :
            classifier.addSample(tracker);
            break;
        case 's'    :
            classifier.save("expressions");
            break;
        case 'l'    :
            classifier.load("expressions");
            break;
    }
}
