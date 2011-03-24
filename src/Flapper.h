//
//  Flapper.h
//  flyingToasters
//
//  Created by Eric Mika on 3/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "stdio.h"
#include "ofMain.h"

class Flapper {
public:
	
	Flapper();
    void updateHands(ofPoint leftHand, ofPoint rightHand);
    void update();
    void draw();
    
private:
    float x, y;
    float vX, vY;
    float ax, ay;
    float gravity;
    
    void flapUp();
    void flapDown();
    
    // input
    ofPoint leftHand, rightHand;
    
    // hand history
    int handHistoryDepth;
    vector<ofPoint> leftHandHistory;
    vector<ofPoint> rightHandHistory;	    
    
    // flap tracking
    float averageLeftVelocity, averageRightVelocity;    
    float lastAverageLeftVelocity, lastAverageRightVelocity;    
    ofPoint averageLeftPoint, averageRightPoint;
    float wingAngle;
    float leftBottom, rightBottom;
    float leftTop, rightTop;
    float leftFlapSize, rightFlapSize;
    float leftFlapSpeed, rightFlapSpeed;    
    int leftFlapReversalTime, rightFlapReversalTime; // time when we last reversed    


};