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
    timeTable =     {9000.0,                     START_MOVIE_SPOT,         START_MOVIE_SPOT + 13170,    START_MOVIE_SPOT + 14370,   START_MOVIE_SPOT + 15890,
                     START_MOVIE_SPOT + 17800,   START_MOVIE_SPOT + 19110, START_MOVIE_SPOT + 20230,    START_MOVIE_SPOT + 22150,   START_MOVIE_SPOT + 26000,
                     START_MOVIE_SPOT + 28050,   START_MOVIE_SPOT + 31000, START_MOVIE_SPOT + 32230,    START_MOVIE_SPOT + 33180,   START_MOVIE_SPOT + 37130,
                     START_MOVIE_SPOT + 37530,   START_MOVIE_SPOT + 38030, START_MOVIE_SPOT + 38530,    START_MOVIE_SPOT + 39140,   START_MOVIE_SPOT + 42140,
                     START_MOVIE_SPOT + 43010,   START_MOVIE_SPOT + 43150, START_MOVIE_SPOT + 44500,    START_MOVIE_SPOT + 45080,   START_MOVIE_SPOT + 47100,
                     START_MOVIE_SPOT + 48180,   START_MOVIE_SPOT + 50040, START_MOVIE_SPOT + 51160,    START_MOVIE_SPOT + 55090,   START_MOVIE_SPOT + 56020,
                     START_MOVIE_SPOT + 56080,   START_MOVIE_SPOT + 56170, START_MOVIE_SPOT + 56550,    START_MOVIE_SPOT + 56550,   START_MOVIE_SPOT + 57190,
                     START_MOVIE_SPOT + 57590,   START_MOVIE_SPOT + 58090, START_MOVIE_SPOT + 58220,    START_MOVIE_SPOT + 59120,   START_MOVIE_SPOT + 61030,
                     START_MOVIE_SPOT + 61430,   START_MOVIE_SPOT + 61930, START_MOVIE_SPOT + 62330,    START_MOVIE_SPOT + 62530,   START_MOVIE_SPOT + 62730,
                     START_MOVIE_SPOT + 63030,   START_MOVIE_SPOT + 64210, START_MOVIE_SPOT + 66050,    START_MOVIE_SPOT + 66350,   START_MOVIE_SPOT + 66650,
                     START_MOVIE_SPOT + 67020,   START_MOVIE_SPOT + 67320, START_MOVIE_SPOT + 67620,    START_MOVIE_SPOT + 68160,   START_MOVIE_SPOT + 68360,
                     START_MOVIE_SPOT + 68660,    START_MOVIE_SPOT + 69110,
                     START_MOVIE_SPOT + 72100,   START_MOVIE_SPOT + 73190, START_MOVIE_SPOT + 75000,    START_MOVIE_SPOT + 77000,   START_MOVIE_SPOT + 78160,
                     START_MOVIE_SPOT + 78360,   START_MOVIE_SPOT + 78260, START_MOVIE_SPOT + 78560,    START_MOVIE_SPOT + 78860,   START_MOVIE_SPOT + 79060,
        
                     START_MOVIE_SPOT + 79100,   START_MOVIE_SPOT + 79400, START_MOVIE_SPOT + 79700,    START_MOVIE_SPOT + 79900,   START_MOVIE_SPOT + 80100,
                    START_MOVIE_SPOT + 80300,    START_MOVIE_SPOT + 80600,
        
                    START_MOVIE_SPOT + 81000,   START_MOVIE_SPOT + 96080
                    };
    sceneTable =    {IN_SUIT_SCENE,             OPENING_START,              COMIC_FACE,                 NORMAL_MOVIE,               SOLID_BOX,
                     NORMAL_MOVIE,              COMIC_FACE,                 NORMAL_MOVIE,               DOT_MOVIE,                  NORMAL_MOVIE,
                     DOT_MOVIE,                 NORMAL_MOVIE,               SOLID_BOX,                  DOT_MOVIE,                  NORMAL_MOVIE,
                     DOT_MOVIE,                 NORMAL_MOVIE,               DOT_MOVIE,                  NORMAL_MOVIE,               PARTICLE_COLOR,
                     NORMAL_MOVIE,              DOT_MOVIE,                  NORMAL_MOVIE,               SOLID_BOX,                  NORMAL_MOVIE,
                     DOT_MOVIE,                 PARTICLE_COLOR,             NORMAL_MOVIE,               SOLID_BOX,                  NORMAL_MOVIE,
                     DOT_MOVIE,                 NORMAL_MOVIE,               DOT_MOVIE,                  NORMAL_MOVIE,               DOT_MOVIE,
                     NORMAL_MOVIE,              DOT_MOVIE,                  SEPARATE_FACE,              NORMAL_MOVIE,               COMIC_FACE,
                     SOLID_BOX,                 NORMAL_MOVIE,               DOT_MOVIE,                  NORMAL_MOVIE,               COMIC_FACE,
                     DOT_MOVIE,                 NORMAL_MOVIE,               PARTICLE_COLOR,             SOLID_BOX,                  NORMAL_MOVIE,
                     SEPARATE_FACE,             COMIC_FACE,                 NORMAL_MOVIE,               DOT_MOVIE,                  NORMAL_MOVIE,
                     DOT_MOVIE,                 NORMAL_MOVIE,
                     SEPARATE_FACE,             DOT_MOVIE,                  SOLID_BOX,                  NORMAL_MOVIE,              SEPARATE_FACE,
                     COMIC_FACE,                DOT_MOVIE,                  PARTICLE_COLOR,             SOLID_BOX,                  NORMAL_MOVIE,
                    DOT_MOVIE,                  COMIC_FACE,                 SOLID_BOX,                  NORMAL_MOVIE,               DOT_MOVIE,
                    NORMAL_MOVIE,               DOT_MOVIE,
        
                    NORMAL_MOVIE,               ENDING
                    };
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
            suitBgmPlayer.unload();
            effectWarningPlayer.stop();
            effectWarningPlayer.unload();
            
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
        case 8:
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
            
            if(ofGetElapsedTimeMillis() > START_MOVIE_SPOT + 43200.0 && ofGetElapsedTimeMillis() < START_MOVIE_SPOT + 44000.0){
                ofImage monoImage = cam.getPixels();
                monoImage.setImageType(OF_IMAGE_GRAYSCALE);
                monoImage.draw(0,0);
            }
            
            switch(numSceneTable%4){
                case 0:
                    dotmovie.draw(mainMovie);
                    break;
                case 1:
                    dotmovie.draw(mainMovie, (numSceneTable%3), size_spect[(int)ofRandom(0,4)]);
                    break;
                case 2:
                    dotmovie.draw(mainMovie, (numSceneTable%3), size_spect[(int)ofRandom(0,4)], size_spect[(int)ofRandom(0,4)]);
                    break;
                case 3:
                    dotmovie.draw(mainMovie, size_spect);
                    break;
            }

            break;
            
        case 4:
            ofBackground(255);
            separateface.draw(cam.getPixels(), tracker.getPosition(), (tracker.getImagePoint(48)+tracker.getImagePoint(54))/2,
                              (tracker.getImagePoint(36)+tracker.getImagePoint(39))/2, (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2,(numSceneTable%2));
            separateface.draw(cam.getPixels(), -tracker.getPosition(), (tracker.getImagePoint(48)+tracker.getImagePoint(54))/2,
                              (tracker.getImagePoint(36)+tracker.getImagePoint(39))/2, (tracker.getImagePoint(42)+tracker.getImagePoint(45))/2, (numSceneTable%2));
            break;
            
        case 5:
            ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
            
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].draw(mainMovie);
            }
            break;
        case 6:
            solidbox.draw(tracker.getRotationMatrix().getRotate(), size_spect[4],(numSceneTable%2));
            break;
        case 7:
            comicface.draw(tracker);
            break;
        case 8:
            ofBackground(0);
            mainMovie.draw(ofGetWidth()/2, ofGetHeight()/2);
            break;
        case 9:
            ofBackground(255,0,0);
            break;
    }
    
//        cam.draw(cam.getWidth(), 0, -cam.getWidth()/3, cam.getHeight()/3);

	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis()), ofGetWidth()/2, ofGetHeight() - 50);
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
