#pragma once

#ifndef MOVINGIMG_H
#define MOVINGIMG_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#define MAX_VEL 5
#define MIN_ALPHA 20
#define MAX_ALPHA 200

class MovingImg {
	public:
		MovingImg();
		MovingImg(ofImage img, ofVec2f position);
		void update();
		
		ofVec2f velocity;
		ofVec2f pos;
		ofImage img;
		int alpha;
};


#endif