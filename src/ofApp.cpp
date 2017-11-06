#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	// setup kinect
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	kinect.setCameraTiltAngle(-5);
	camW = kinect.getWidth();
	camH = kinect.getHeight();
	// create pen
	pens.push_back(Pen(camW, camH));
	//pen = Pen(camW, camH);
	index = 0;
	ofSetBackgroundColor(ofColor(237, 155, 64));
	lightOn = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	//update positions of already drawn images
	for (int i = 0; i < index; ++i) {
		pens[i].updateImagePos();
	}
	// get position of light
	ofVec2f brightest = getBrightest();
	// if a brightest point is found and the current FBO is being drawn to
	if (brightest.x != -1 && pens[index].isDrawing()) {
		// if continuing the line
		if (lightOn) {
			pens[index].update(brightest, lightOn);
		}
		// otherwise the light was turned off and a new line needs to be drawn
		else {
			pens[index].update(brightest, lightOn);
			lightOn = true;
		}
		// draw position to canvas
		
	}
	// if a brightest point wasn't found then the light is not on
	else {
		lightOn = false;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	// draw all images, including one being drawn
	for (int i = 0; i < pens.size(); ++i) {
		pens[i].drawFbo();
	}
}

// Returns brightest pixel in kinect video as ofVec2f if the brightest pixel
// is greater than 250, else returns ofVec2f(-1, 0)
ofVec2f ofApp::getBrightest() {
	ofPixels pix = kinect.getPixels();
	int maxBright = 0;
	ofVec2f p;
	// check every pixel for brightest pixel
	for (int x = 0; x < camW; ++x) {
		for (int y = 0; y < camH; ++y) {
			int currBright = pix.getColor(x, y).getBrightness();
			if (currBright > maxBright) {
				maxBright = currBright;
				p = ofVec2f(x, y);
			}
		}
	}

	if (maxBright > 250) {
		return p;
	}
	return ofVec2f(-1, 0);
}

//--------------------------------------------------------------
// if the current drawing is finished create a new one to be drawn to
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RETURN) {
		// the drawing is now finished, get image
		pens[index].setDrawing(false);
		pens.push_back(Pen(camW, camH));
		lightOn = false;
		++index;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
