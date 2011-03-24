//
//  Sprite.h
//  flyingToasters
//
//  Created by Eric Mika on 3/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "stdio.h"
#include "ofMain.h"

class Mover {
    public:
    Mover();
    virtual void update();
    virtual void draw();
    float gravity;    

protected:
    float x, y;
    float vX, vY;
    float ax, ay;    
};
	