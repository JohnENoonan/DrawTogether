#include "pen.h"

// Constructor is passed dimension of kinect video
Pen::Pen(int w, int h) {
	//init fbo
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	// size of kinect video
	camW = w;
	camH = h;
	// settings for the fbo image
	fbo.begin();
	ofClear(255, 255, 255, 0);
	ofSetBackgroundColor(ofColor(0, 0, 0, 0));
	ofSetCircleResolution(500);
	fbo.end();
	drawing = true;
	brushSize = 5;
	// init to be somewhere far from canvas
	prevPos = ofVec2f(-100, -100);
	velocity = ofVec2f(ofRandom(-1 * MAX_VEL, MAX_VEL), ofRandom(-1 * MAX_VEL, MAX_VEL));
	imgPos = ofVec2f(0,0);
}

// called when this is drawing. Adds the new position to the drawing if 
// past threshold
void Pen::update(const ofVec2f& pos) {
	// adjust pos so it is not mirror image
	ofVec2f currPos = ofVec2f(camW - pos.x, pos.y);
	// distance from previously drawn point
	float dist = ofDist(currPos.x, currPos.y, prevPos.x, prevPos.y);
	// if the points are far enough away from eachother that they are distinct
	if (dist > MIN_DIST) {
		// continue the line with the new point
		if (dist < 3 * MIN_DIST) {
			drawHelper(currPos);
			// update previous drawn circle
			prevPos = currPos;
			// update timer 
		}
		// if the light was turned of to make a new line
		else {
			fbo.begin();
			ofSetColor(ofColor(255, 238, 219));
			ofDrawCircle(mapToCanvas(currPos), brushSize);
			fbo.end();
			// update previous drawn circle
			prevPos = currPos;
		}
	}
}

// helper function to draw to fbo given new position
// the drawing uses a Catmull-Rom spline and draws circles on top of it to 
// simulate width
void Pen::drawHelper(const ofVec2f& pos) const {
	// map points to canvas size
	ofVec2f p = mapToCanvas(pos);
	ofVec2f pp = mapToCanvas(prevPos);
	fbo.begin();
	// generate spline between points
	ofPolyline line;
	line.curveTo(pp); // handle
	line.curveTo(pp);
	line.curveTo(p);
	line.curveTo(p); // handle
	line.simplify(.5);
	float perim = line.getPerimeter();
	// draw circles on line
	for (int p = 0; p < ((int)perim); ++p) {
		ofVec3f point = line.getPointAtPercent(p / perim);
		ofDrawCircle(point, brushSize);
	}
	fbo.end();
}

// helper to map the point from kinect camera to wherever it 
// needs to be on the canvas
ofVec2f Pen::mapToCanvas(const ofVec2f& old) const {
	float x = ofMap(old.x, 0, camW, 0, ofGetWidth());
	float y = ofMap(old.y, 0, camH, 0, ofGetHeight());
	return ofVec2f(x, y);
}

void Pen::updateImagePos() {
	imgPos += velocity;
}

void Pen::setDrawing(bool b) {
	drawing = b;
}

// when the drawing is finished clear fbo and return the drawing as image
//MovingImg Pen::getImage() const {
//	drawing = false;
//	ofPixels pix;
//	fbo.readToPixels(pix);
//	fbo.clear();
//	int minX, minY, maxX, maxY;
//	// get minX
//	for (int x = 0; x < camW; ++x) {
//		for (int y = 0; y < camH; ++y) {
//			if (pix.getColor(x,y) != ofColor(0, 0, 0, 0)) {
//				minX = x;
//			}
//		}
//	}
//	// get MaxX
//	for (int x = camW-1; x >= 0; --x) {
//		for (int y = 0; y < camH; ++y) {
//			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
//				maxX = x;
//			}
//		}
//	}
//	// get minY
//	for (int y = 0; y < camH; ++y) {
//		for (int x = 0; x < camW; ++x) {
//			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
//				minY = y;
//			}
//		}
//	}
//	// get maxY
//	for (int y = camH-1; y >= 0; --y) {
//		for (int x = 0; x < camW; ++x) {
//			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
//				maxY = y;
//			}
//		}
//	}
//	// image that represents all drawn pixels from fbo
//	ofImage img;
//	img.allocate(maxX - minX, maxY - minY, OF_IMAGE_COLOR_ALPHA);
//	pix.crop(minX, minY, maxX - minX, maxY - minY);
//	img.setFromPixels(pix);
//	return MovingImg(img, ofVec2f(img.getWidth() / 2, img.getHeight() / 2));
//}

// draw this FBO to main canvas
void Pen::drawFbo() {
	// if this is being drawn to, draw at origin
	if (drawing) {
		fbo.draw(0,0);
	}
	else {
		// otherwise draw at position specified
		fbo.draw(imgPos);
		// bounce of screen if image is moving too far from canvas
		if (imgPos.x > 2*ofGetWidth()|| imgPos.x < -ofGetWidth()) {
			velocity = ofVec2f(velocity.x*-1, velocity.y);
		}
		if (imgPos.y > 2*ofGetHeight() || imgPos.y < -ofGetHeight()) {
			velocity = ofVec2f(velocity.x, velocity.y*-1);
		}
	}
}