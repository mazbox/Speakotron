/*
 *  Mouth.cpp
 *  mouthsynth
 *
 *  Created by Marek Bereza on 04/09/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Mouth.h"


void Mouth::update(const ofRectangle &rect) { 


	state = false;
	filter = 0;
	

    // find x, y, width, height
    this->x = rect.x;
    this->y = rect.y;
    
    this->width  = rect.width;
    this->height = rect.height;
	
	float pitchInput = y+(height/2); // this is the vertical centre of the mouth
	pitch = ofMap(pitchInput, 0, 320, 0, 1);
	pitch = ofMap(pitch, 0.6, 0.1, 0, 1);
	pan = ofMap(x + width/2, 0, width, 0, 1);
	
	
	
	pos = ofPoint(x + width/2, y + height/2);
	


/*



    // this is some weird ratio of width to height

	if(state==true) {
		filter = (rightMost-leftMost)/width;
	}
	
	// find filter and whether the state is on or not
	
	if(state&&!lastState) {
		justOpened = true;
	} else {
		justOpened = false;
	}
	
	lastState = state;
	*/
}


void Mouth::draw() {
	ofSetHexColor(0xFF0000);
    ofRect(*this);
}
