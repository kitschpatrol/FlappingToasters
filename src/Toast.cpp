//
//  Toast.cpp
//  flyingToasters
//
//  Created by Eric Mika on 3/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Toast.h"


Toast::Toast() {
    
    if(ofRandom(0, 1) > 0.5) {
        toastGraphic.loadImage("mediumToast.png");        
    }
    else {
        toastGraphic.loadImage("lightToast.png");            
    }
    
    vX = -1;
    vY = 0.5;
    x = ofRandom(ofGetWidth(), ofGetWidth() * 1.5);
    y = ofRandom(-ofGetHeight(), ofGetHeight() * 0.25);
}

void Toast::update() {
    x += vX;
    y += vY;
    
    // loop the toast
    if (((x + toastGraphic.getWidth()) < 0) || (y > ofGetHeight())) {
        x = ofRandom(ofGetWidth(), ofGetWidth() * 1.5);
        y = ofRandom(-ofGetHeight(), ofGetHeight() * 0.25);
    }
}

void Toast::draw() {
    toastGraphic.draw(x, y);
}