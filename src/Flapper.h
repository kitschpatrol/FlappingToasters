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
#include "Toast.h"

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
    bool takePhoto;
    
private:
    int color;
    int rollTimer;
    
    void flap();
    void flapUp();
    void flapDown();
    void clapIn();
    void clapOut();
    
    
    int minFlapInterval;
    int lastFlapFrame;
    
    vector<Toast> toastPops;
    float timeLastToastPop;
    
    // input
    ofPoint leftHand, rightHand;
    
    // hand history
    int handHistoryDepth;
    vector<ofPoint> leftHandHistory;
    vector<ofPoint> rightHandHistory;	    
    
    // flap tracking
    float averageLeftVelocityX, averageRightVelocityX, averageLeftVelocityY, averageRightVelocityY;    
    float lastAverageLeftVelocityX, lastAverageRightVelocityX, lastAverageLeftVelocityY, lastAverageRightVelocityY;    
    ofPoint averageLeftPoint, averageRightPoint;
    float wingAngle;
    float leftCurrentX, rightCurrentX, leftCurrentY, rightCurrentY;
    float leftBottom, rightBottom;
    float leftTop, rightTop;
    float leftOuter, rightOuter;
    float leftInner, rightInner;
    float leftFlapSize, rightFlapSize;
    float leftClapSize, rightClapSize;
    float leftFlapSpeed, rightFlapSpeed;
    float leftClapSpeed, rightClapSpeed;
    int leftFlapReversalTime, rightFlapReversalTime; // time when we last reversed
    int leftClapReversalTime, rightClapReversalTime;

    // sound fx
    ofSoundPlayer flap1;
    ofSoundPlayer flap2;    
    ofSoundPlayer toastPop;
    
    // sprites
    int spriteCount;
    ofImage * sprites;
    ofImage * activeSprite;
};