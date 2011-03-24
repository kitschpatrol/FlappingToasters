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
	
    
    
    
    //	accordionSample.loadSound("27355__junggle__accordeon_21.wav");
    //	accordionSample.setMultiPlay(true);
    //	
    //	accordionBreath.loadSound("19866__kostasvomvolos__breath_7.wav");
	
	handHistoryDepth = 10; // store the last 10 hand positions, newest first
    //	playDelay = 10; // frames between cues
    //	lastPlay = 0;
    
    
    averageRightVelocity = 0;
    lastAverageRightVelocity = 0;
}

void testApp::update() {
	context.update();
	user.update();
	ofSoundUpdate();
	
	// find the hands
	for (int i = 0; i < user.getTrackedUsers().size(); i++) {
		ofxTrackedUser* tracked = user.getTrackedUser(i);
		if (tracked != NULL && tracked->left_lower_arm.found && tracked->right_lower_arm.found) {
			leftHand = tracked->left_lower_arm.end;
			rightHand = tracked->right_lower_arm.end;
			break;
		}
	}
	
	// add hand positions to history
	if (leftHandHistory.size() <= handHistoryDepth) {
		leftHandHistory.insert(leftHandHistory.begin(), leftHand);
	}
	
	if (rightHandHistory.size() <= handHistoryDepth) {
		rightHandHistory.insert(rightHandHistory.begin(), rightHand);
	}
	
	// remove hand positions from history
	if (leftHandHistory.size() > handHistoryDepth) {
		leftHandHistory.pop_back();
	}
	
	if (rightHandHistory.size() > handHistoryDepth) {
		rightHandHistory.pop_back();
	}
    
    if( user.getTrackedUsers().size() > 0 ){
        
        
        // Find average velocity
        float leftVelocityAccumulator = 0;
        float rightVelocityAccumulator = 0;
        ofPoint leftPointAccumulator;
        ofPoint rightPointAccumulator;
        
        for (int i = 0; i < handHistoryDepth - 1; i++) {
            leftVelocityAccumulator += leftHandHistory[i].y - leftHandHistory[i + 1].y;            
            rightVelocityAccumulator += rightHandHistory[i].y - rightHandHistory[i + 1].y;

            leftPointAccumulator.x += leftHandHistory[i].x;
            leftPointAccumulator.y += leftHandHistory[i].y;
            
            rightPointAccumulator.x += rightHandHistory[i].x;
            rightPointAccumulator.y += rightHandHistory[i].y;            
        }

        averageLeftVelocity = leftVelocityAccumulator / (handHistoryDepth - 1);        
        averageRightVelocity = rightVelocityAccumulator / (handHistoryDepth - 1);

        averageLeftPoint.x = leftPointAccumulator.x / (handHistoryDepth - 1);
        averageLeftPoint.y = leftPointAccumulator.y / (handHistoryDepth - 1);

        averageRightPoint.x = rightPointAccumulator.x / (handHistoryDepth - 1);
        averageRightPoint.y = rightPointAccumulator.y / (handHistoryDepth - 1);
        
        // determine direction
        float velocityThreshold = 5;
        
        if ((averageLeftVelocity >= velocityThreshold) && (lastAverageLeftVelocity < velocityThreshold)) {
            cout << "Left Starting down" << endl;
            leftTop = leftHand.y;
        }
        
        if ((averageLeftVelocity <= velocityThreshold) && (lastAverageLeftVelocity > velocityThreshold)) {
            cout << "Left Starting up" << endl;
            leftBottom = leftHand.y;
        }                
        
        if ((averageRightVelocity >= velocityThreshold) && (lastAverageRightVelocity < velocityThreshold)) {
            cout << "Right Starting down" << endl;
            rightTop = rightHand.y;
        }
        
        if ((averageRightVelocity <= velocityThreshold) && (lastAverageRightVelocity > velocityThreshold)) {
            cout << "Right Starting up" << endl;
            rightBottom = rightHand.y;
        }

        // store last for comparison on next frame
        lastAverageRightVelocity = averageRightVelocity;
        lastAverageLeftVelocity = averageLeftVelocity;
    
        // calculate size of latest flap
        leftFlapSize = abs(leftTop - leftBottom);
        rightFlapSize = abs(rightTop - rightBottom);
        
        // figure out flap angle
        
        float wingAngle = atan2(averageRightPoint.y - averageLeftPoint.y, averageRightPoint.x - averageLeftPoint.x) * 180 / PI;
        

        cout << "Left Spread: " << leftFlapSize << "\tLeft Top: " << leftTop << "\tLeft Bottom: " << leftBottom << "\tWing Angle: " << wingAngle << endl;
    }
    
    
	// find hand velocity (positive is "apart" negative is "together")
	
    //	float distance = ofDist(leftHand.x, leftHand.y, rightHand.x, rightHand.y);
    //	float lastDistance = ofDist(leftHandHistory[1].x, leftHandHistory[1].y, rightHandHistory[1].x, rightHandHistory[1].y);
    //	
    //    
    //	float velocity = distance - lastDistance;
	
    //	cout << "VELOCITY: " << velocity << endl;
	
    //	if ((velocity < -5) && ((ofGetFrameNum() - lastPlay) > playDelay)) {
    //		lastPlay = ofGetFrameNum();
    //        accordionSample.play();	
    //        accordionSample.setSpeed(ofMap(leftHand.y, 0, 480, 2, .3));
    //        
    //	}
    //	
    //	if (velocity > 5) {
    //		if(!accordionBreath.getIsPlaying()) {
    //			accordionBreath.play();	
    //		}
    //	}	
    
    
    
    //	// log hand histories, for debug
    //	cout << "LEFT: ";
    //	for (int i = 0; i < leftHandHistory.size(); i++) {
    //		cout << "(" << leftHandHistory[i].x << ", " << leftHandHistory[i].y << ") ";
    //	}
    //	cout << endl;
}


void testApp::draw() {
	ofSetLineWidth(1);
	ofSetColor(255, 255, 255);
	
	depth.draw(640,0,640,480);
	rgb.draw(0, 0, 640, 480);
	user.draw();
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	user.drawUserMasks(0, 0);
	glDisable(GL_BLEND);
	
	ofSetColor(255, 0, 0);
	ofCircle(leftHand.x, leftHand.y, 10);
	ofCircle(rightHand.x, rightHand.y, 10);				
    //	ofSetLineWidth(200);
    //	ofLine(leftHand.x, leftHand.y, rightHand.x, rightHand.y);
    
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
    accordionSample.play();	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
