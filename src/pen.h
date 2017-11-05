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
		// need to be overloaded, do not call no param constructor
		Pen() : Pen(640, 480) {}
		Pen(int w, int h);
		void update(ofVec2f pos); // update drawin
		void updateImagePos(); // update finished 
		
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
		void drawHelper(ofVec2f pos);

		ofFbo fbo; // what is drawn to
		ofColor col;
		//ofPolyline currentLine;

		int camW, camH; // image dimensions
		ofVec2f prevPos, imgPos, velocity;


		float brushSize;
		bool drawing; // flag
};

#endif