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
		void update(const ofVec2f& pos); // update drawin
		void updateImagePos(); // update finished 
		
		// getters
		ofColor getColor() const { return col; }
		float getBrushSize() const  { return brushSize; }
		bool isDrawing() const { return drawing; }
		void drawFbo();
		//MovingImg getImage() const;
		// setters
		void setDrawing(bool b);

	private:
		void drawHelper(const ofVec2f& pos) const;
		ofVec2f mapToCanvas(const ofVec2f& old) const;

		ofFbo fbo; // what is drawn to
		ofColor col;

		int camW, camH; // image dimensions
		ofVec2f prevPos, imgPos, velocity;


		float brushSize;
		bool drawing; // flag
};

#endif