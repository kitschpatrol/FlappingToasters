#include "testApp.h"
void testApp::setup() {
	ofBackground(0, 0, 0);
	ofSetFrameRate(60);
	
	context.setup();
	context.setupUsingXMLFile();
	depth.setup(&context);
	rgb.setup(&context);
	user.setup(&context, &depth, &rgb);
	
	depth.toggleRegisterViewport(&rgb);
	context.toggleMirror();	
	
    // control panel
	panel.setup("Control Panel", ofGetWidth() - 315, 5, 300, 600);	
	panel.addPanel("Physics");	
	panel.addSlider("flap power", "flapPower", 7.7, 0, 10, false);
	panel.addSlider("gravity", "gravity", .83, 0, 5, false);    
    
    
    // create flappers
    flappers = new Flapper[15];    
    
    
    valkyries.loadSound("valkyries.wav");
}

void testApp::update() {
	context.update();
	user.update();
	ofSoundUpdate();
	
	// find the hands via openni
    
	for (int i = 0; i < user.getTrackedUsers().size(); i++) {
		ofxTrackedUser* tracked = user.getTrackedUser(i);
        


        
        
        if (tracked != NULL && tracked->left_lower_arm.found && tracked->right_lower_arm.found) {

            if(!valkyries.getIsPlaying()) {
                valkyries.play();
            }            
            
            
            cout << "Tracked hands of user: " << tracked->id << endl;            
            flappers[tracked->id - 1].updateHands(tracked->left_lower_arm.end, tracked->right_lower_arm.end);
        }
	}
    
    
    if (user.getTrackedUsers().size() == 0) {
        if (valkyries.getIsPlaying()) {
            valkyries.stop();
            valkyries.setPosition(0.0);
        }             
    }
    
    // update the flappers
    for (int i = 0; i < 15; i++) {
        
        flappers[i].flapPower = panel.getValueF("flapPower");
        flappers[i].gravity = panel.getValueF("gravity");
        flappers[i].update();
    }
}


void testApp::draw() {
	ofSetLineWidth(1);
	ofSetColor(255, 255, 255);
	
	depth.draw(0, 0, 640, 480);
	user.draw();
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	user.drawUserMasks(0, 0);
	glDisable(GL_BLEND);    
    
    // draw the flappers
    for (int i = 0; i < 15; i++) {
        flappers[i].draw();
    }    
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
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
	
}
