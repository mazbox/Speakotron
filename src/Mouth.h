/*
 *  Mouth.h
 *  mouthsynth
 *
 *  Created by Marek Bereza on 04/09/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "ofMain.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxCvContourFinder.h"
class Mouth: public ofRectangle {
public:
	Mouth(){justOpened = false;};
	void update(const ofRectangle &rect);	

	ofRectangle openingRect;
	
	bool isOpen() { return state; }
	float getPitch() { return pitch; }
	float getFilter() { return filter; }
	float getPan() { return pan; }
	bool state;
	float filter;
	float pan;
	float pitch;
	bool lastState;
	bool justOpened;
    void draw();
	ofPoint getPos() {
		return pos;
	}
	ofPoint pos;
	
    bool mouthJustOpened() {
		return justOpened;
	}
};