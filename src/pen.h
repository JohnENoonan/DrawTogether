#pragma once

#ifndef PEN_H
#define PEN_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "movingImg.h"

#define MIN_DIST 10
#define MAX_VEL 3
#define MIN_ALPHA 20
#define MAX_ALPHA 200

class Pen {
	public:
		Pen();
		Pen(int w, int h);
		void update(ofVec2f pos);
		void updateImagePos();
		
		// getters
		ofColor getColor() { return col; }
		float getBrushSize() { return brushSize; }
		bool isDrawing() { return drawing; }
		void drawFbo();
		MovingImg getImage();
		ofFbo getFbo();
		void drawImage();
		// setters
		void setDrawing(bool b);

	private:
		ofFbo fbo;
		ofColor col;

		int camW, camH;
		ofVec2f prevPos, imgPos, velocity;

		float brushSize;
		bool drawing;

};

#endif