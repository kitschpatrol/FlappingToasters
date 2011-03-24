//
//  Toast.h
//  flyingToasters
//
//  Created by Eric Mika on 3/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "stdio.h"
#include "ofMain.h"
#include "Mover.h"

class Toast : public Mover {
public:
	
	Toast();
    virtual void update();
    virtual void draw();    
    
private:
    ofImage toastGraphic;
    
};