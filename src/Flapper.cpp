//
//  Flapper.cpp
//  flyingToasters
//
//  Created by Eric Mika on 3/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Flapper.h"

Flapper::Flapper() {
    // constructor
	cout << "Creating flapper" << endl;
    
    active = false;
    
    handHistoryDepth = 10; // store the last 10 hand positions, newest first
    
    averageLeftVelocity, averageRightVelocity = 0;
    leftFlapReversalTime, rightFlapReversalTime = 0;
    leftFlapSpeed, rightFlapSpeed = 0;

    x = ofGetWidth();
    y = 0;
    
    vX = 0;
    vY = 0;
    
    ax = 0;
    ay = 0;
    
    gravity = 0.2;
    
    color = round(ofRandom(0, 255));
    
    flap1.loadSound("flap1.wav");
    flap1.setVolume(0.5);
    flap1.setMultiPlay(true);

    flap2.loadSound("flap2.wav");
    flap2.setVolume(0.5);    
    flap2.setMultiPlay(true); 

    
    // load images
    spriteCount = 20;
    sprites = new ofImage[spriteCount];
    for (int i = 0; i < spriteCount; i++) {
        sprites[i].loadImage("roll" + ofToString(i + 1) + ".png");
    }
    
    // wings level by defaut
    activeSprite = &sprites[18];    
    
    gracePeriod = 10 * 1000;

}

void Flapper::flapUp() {
    cout << "FLAP UP" << endl;
    vY -= flapPower;

    if((rand() / RAND_MAX) > 0.5) {
        flap1.play();
    }
    else {
        flap2.play();        
    }        
    
}

void Flapper::flapDown() {
    cout << "FLAP DOWN" << endl;
    

}

void Flapper::update() {
    x += vX;
    y += vY;

    
    // ground
    if (y > (ofGetHeight() - activeSprite->getHeight())) {
        y = ofGetHeight() - activeSprite->getHeight();
        vY = 0;
    }
    
    if(active && ((ofGetElapsedTimeMillis() - timeLastHandUpdate) > gracePeriod)) {
        active = false;
        cout << " GRACE PERIOD IS OVER " << endl;
    }
    
    if(active) {
        vX = -1;
        vY += gravity;        
    }
    else {
        vX = 0;
        activeSprite = &sprites[0];
    }
    
    // which third of the arc are we in
    

    float flapPercent = leftCurrent / (leftBottom - leftTop + .001);
    
    if(active) cout << "FLAP PERCENT: " << flapPercent << endl;
    
    if(flapPercent < 33) {
        // wings down
        activeSprite = &sprites[19];
    }
    else if ((flapPercent >= 33) && (flapPercent <= 66)) {
        // wings level
        activeSprite = &sprites[18];
    }
    else if (flapPercent > 66) {
        // wings up
        activeSprite = &sprites[17];        
    }
    
    // loop the toaster
    if ((x + activeSprite->getWidth()) < 0) {
        x = ofGetWidth();
        y = 0;
    }    
    
}

void Flapper::draw() {
    activeSprite->draw(x, y);
    
}

void Flapper::updateHands(ofPoint leftHand, ofPoint rightHand) {
    
    active = true;
    timeLastHandUpdate = ofGetElapsedTimeMillis();
    
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
    
    leftCurrent = leftHand.y;
    rightCurrent = rightHand.y;    
    
    if ((averageLeftVelocity >= velocityThreshold) && (lastAverageLeftVelocity < velocityThreshold)) {
        //cout << "Left Starting down" << endl;
        
        //distance over time
        leftTop = leftHand.y;            
        leftFlapSpeed = (float)leftFlapSize / (ofGetElapsedTimeMillis() - leftFlapReversalTime);
        leftFlapReversalTime = ofGetElapsedTimeMillis();
        
        flapUp();  
    }
    
    if ((averageLeftVelocity <= velocityThreshold) && (lastAverageLeftVelocity > velocityThreshold)) {
        //cout << "Left Starting up" << endl;
        leftBottom = leftHand.y;
        leftFlapSpeed = (float)leftFlapSize / (ofGetElapsedTimeMillis() - leftFlapReversalTime);
        leftFlapReversalTime = ofGetElapsedTimeMillis();     
        flapDown();        
      
    }                
    
    if ((averageRightVelocity >= velocityThreshold) && (lastAverageRightVelocity < velocityThreshold)) {
        //cout << "Right Starting down" << endl;
        rightTop = rightHand.y;
        rightFlapSpeed = (float)rightFlapSize / (ofGetElapsedTimeMillis() - rightFlapReversalTime);
        rightFlapReversalTime = ofGetElapsedTimeMillis();
        flapUp();          
        
    }
    
    if ((averageRightVelocity <= velocityThreshold) && (lastAverageRightVelocity > velocityThreshold)) {
        //cout << "Right Starting up" << endl;
        rightBottom = rightHand.y;
        rightFlapSpeed = (float)rightFlapSize / (ofGetElapsedTimeMillis() - rightFlapReversalTime);
        rightFlapReversalTime = ofGetElapsedTimeMillis();
        flapDown();        
      
    }
    
    // store last for comparison on next frame
    lastAverageRightVelocity = averageRightVelocity;
    lastAverageLeftVelocity = averageLeftVelocity;
    
    // calculate size of latest flap
    leftFlapSize = abs(leftTop - leftBottom);
    rightFlapSize = abs(rightTop - rightBottom);
    
    // figure out fap angle
    wingAngle = atan2(averageRightPoint.y - averageLeftPoint.y, averageRightPoint.x - averageLeftPoint.x) * 180 / PI;
    
    //cout << "Left Spread: " << leftFlapSize << "\tLeft Top: " << leftTop << "\tLeft Bottom: " << leftBottom << "\tLeft Speed: " << leftFlapSpeed << "\tWing Angle: " << wingAngle << endl;    
}