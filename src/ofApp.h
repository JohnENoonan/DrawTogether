#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "pen.h"
#include "movingImg.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec2f getBrightest();

		ofxKinect kinect; // used as camera right now
		//Pen pen; // drawing class
		//std::vector<MovingImg> images;
		std::vector<Pen> pens; // vector of drawings, pens[index] is active
		int camW, camH, index;
		bool lightOn; // flag for whether the light is on or not
				
};
