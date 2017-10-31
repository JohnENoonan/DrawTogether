#include "ofApp.h"
#define ANGLE 0

//--------------------------------------------------------------
void ofApp::setup(){
	// setup kinect
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	kinect.setCameraTiltAngle(ANGLE);
	camW = kinect.getWidth();
	camH = kinect.getHeight();
	pens.push_back(Pen(camW, camH));
	//pen = Pen(camW, camH);
	index = 0;
	ofSetBackgroundColor(ofColor(237, 155, 64));
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	
	for (int i = 0; i < index; ++i) {
		pens[i].updateImagePos();
	}
	ofVec2f brightest = getBrightest();
	if (brightest.x != -1 && pens[index].isDrawing()) {
		pens[index].update(brightest);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//kinect.draw(0,0);	
	/*pen.drawFbo();*/
	ofDrawBitmapString(camW, 600, 200);
	ofDrawBitmapString(camH, 700, 200);
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
void ofApp::keyPressed(int key){
	if (key == OF_KEY_RETURN) {
		// the drawing is now finished, get image
		pens[index].setDrawing(false);
		pens.push_back(Pen(camW, camH));
		++index;
		/*if (pen.isDrawing()) {
			images.push_back(pen.getImage());
		}
		else {
			pen.setDrawing(true);
		}*/
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
