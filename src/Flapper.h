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
#include "Mover.h"

class Flapper : public Mover {
public:
	
	Flapper();
    virtual void update();
    virtual void draw();    
    void updateHands(ofPoint leftHand, ofPoint rightHand);
    float flapPower;
    bool active;
    int gracePeriod;
    int timeLastHandUpdate;
    
private:
    int color;
    
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
    float leftCurrent, rightCurrent;
    float leftBottom, rightBottom;
    float leftTop, rightTop;
    float leftFlapSize, rightFlapSize;
    float leftFlapSpeed, rightFlapSpeed;    
    int leftFlapReversalTime, rightFlapReversalTime; // time when we last reversed    

    // sound fx
    ofSoundPlayer flap1;
    ofSoundPlayer flap2;    
    
    // sprites
    int spriteCount;
    ofImage * sprites;
    ofImage * activeSprite;

};