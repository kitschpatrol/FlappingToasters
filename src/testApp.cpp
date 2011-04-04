#include "testApp.h"
void testApp::setup() {
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	
    
    context.setup();
    
	depth.setup(&context);
	rgb.setup(&context);
	user.setup(&context);
	
    // using hand tracking went worse than expected
	// hands.setup(&context);
	// hands.setSmoothing(0.1);		// built in openni hand track smoothing...
	// hands.setFilterFactors(0.1);	// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with    
    
	user.setSmoothing(0.1); // built in openni skeleton smoothing...
	user.setUseMaskPixels(true);
	user.setUseCloudPoints(false);    
    
    
	context.toggleRegisterViewport();
	context.toggleMirror();
	
    // control panel
	panel.setup("Control Panel", ofGetWidth() - 315, 5, 300, 200);	
	panel.addPanel("Physics");	
	panel.addSlider("flap power", "flapPower", 3.4, 0, 10, false);
	panel.addSlider("gravity", "gravity", .14, 0, 5, false);    
    drawKinect = true;
    
    // create flappers
    flapperCount = 15;
    flappers = new Flapper[flapperCount];    
    
    // create toast
    toastCount = 11;
    toasts = new Toast[toastCount];
    
    valkyries.loadSound("valkyries.wav");
}

void testApp::update() {
	ofSoundUpdate();
    
	context.update();
    depth.update();
    rgb.update();
	user.update();    

	// find the hands via openni
    
    int pairsOfHandsFound = 0;
    
    // starts at 1...
	for (int i = 1; i <= user.getNumberOfTrackedUsers(); i++) {

		ofxTrackedUser* tracked = user.getTrackedUser(i);
        
        if(tracked != NULL) {
            cout << "Tracked is not null: " << tracked->id << endl;
        }
        
        if ((tracked != NULL) && tracked->left_lower_arm.found && tracked->right_lower_arm.found) {
            pairsOfHandsFound++;
            
            
            // start the music
            if(!valkyries.getIsPlaying()) {
                valkyries.play();
            }            
            
            cout << "Tracked hands of user: " << tracked->id << endl;
            cout << "left hand: " << tracked->left_lower_arm.position[0].X << endl;
            flappers[tracked->id - 1].updateHands(tracked->left_lower_arm.position[1], tracked->right_lower_arm.position[1]);
        }
	}
    
    cout << "Found " << pairsOfHandsFound << " pairs of hands." << endl;
    
    // stop the music and seek to the beginning if no one is playing
    if (pairsOfHandsFound == 0) {
        if (valkyries.getIsPlaying()) {
            valkyries.stop();
            valkyries.setPosition(0.0);
        }             
    }
    
    // update the toast
    for (int i = 0; i < toastCount; i++) {
        toasts[i].update();
    }        
    
    // update the flappers
    for (int i = 0; i < flapperCount; i++) {
        flappers[i].flapPower = panel.getValueF("flapPower");
        flappers[i].gravity = panel.getValueF("gravity");
        flappers[i].update();
    }
}


void testApp::draw() {
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    
    
    ofEnableAlphaBlending();
    // draw the toast
    for (int i = 0; i < toastCount; i++) {
        toasts[i].draw();
    }    
    
    // draw the flappers
    for (int i = 0; i < flapperCount; i++) {
        flappers[i].draw();
    }
    
    ofDisableAlphaBlending();
    
    
    
    
    if (drawKinect) {
        ofPushMatrix();
        ofTranslate(ofGetWidth() - 320, ofGetHeight() - 240);
        ofScale(0.5, 0.5);
        
        rgb.draw(0, 0, 640, 480);    
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        // method is gone ? user.drawUserMasks(0, 0);
        glDisable(GL_BLEND);    
        
        user.draw();    
        // hands.drawHands();
        
        ofSetColor(255, 255, 255);
        ofSetLineWidth(1);
        ofNoFill();
        ofRect(0, 0, 640, 480);
        ofSetLineWidth(0);    
        ofSetColor(255, 255, 255);    
        ofPopMatrix();    
    }
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    
    if (key == 'k') {
        drawKinect = !drawKinect;
    }    
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	cout << "resized!" << endl;
}
