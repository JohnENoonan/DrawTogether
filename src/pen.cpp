#include "pen.h"

// Constructor is passed dimension of video
Pen::Pen(int w, int h) {
	//init fbo
	fbo.allocate(w, h, GL_RGBA);
	// size of kinect video
	camW = w;
	camH = h;
	// settings for the fbo image
	fbo.begin();
	ofClear(255, 255, 255, 0);
	ofSetBackgroundColor(ofColor(0, 0, 0, 0));
	ofSetCircleResolution(100);
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
void Pen::update(ofVec2f pos) {
	// adjust pos so it is not mirror image
	pos = ofVec2f(camW - pos.x, pos.y);
	// distance from previously drawn point
	float dist = ofDist(pos.x, pos.y, prevPos.x, prevPos.y);
	// if the points are far enough away from eachother that they are distinct
	if (dist > MIN_DIST) {
		// continue the line with the new point
		if (dist < 8 * MIN_DIST) {
			drawHelper(pos);
			// update previous drawn circle
			prevPos = pos;
		}
		// if the light was turned of to make a new line
		else {
			fbo.begin();
			ofSetColor(ofColor(255, 238, 219));
			ofDrawCircle(pos, brushSize);
			fbo.end();
			// update previous drawn circle
			prevPos = pos;
		}
	}
}

// helper function to draw to fbo given new position
// the drawing uses a Catmull-Rom spline and draws circles ontop of it to 
// simulate width
void Pen::drawHelper(ofVec2f pos) {
	float x = ofMap(pos.x, 0, camW, 0, 1280);
	float px = ofMap(prevPos.x, 0, camW, 0, 1280);
	float y = ofMap(pos.y, 0, camH, 0, 720);
	float py = ofMap(prevPos.y, 0, camH, 0, 720);
	ofVec2f p = ofVec2f(x, y);
	ofVec2f pp = ofVec2f(px, py);
	fbo.begin();
	ofPolyline line;
	line.curveTo(pp); // handle
	line.curveTo(pp);
	line.curveTo(p);
	line.curveTo(p); // handle
	float perim = line.getPerimeter();
	// draw circles on line
	for (int p = 0; p < ((int)perim); ++p) {
		ofVec3f point = line.getPointAtPercent(p / perim);
		ofDrawCircle(point, brushSize);
	}
	fbo.end();
}

void Pen::updateImagePos() {
	imgPos += velocity;
}

void Pen::setDrawing(bool b) {
	drawing = b;
}

// when the drawing is finished clear fbo and return the drawing as image
MovingImg Pen::getImage() {
	drawing = false;
	ofPixels pix;
	fbo.readToPixels(pix);
	fbo.clear();
	int minX, minY, maxX, maxY;
	// get minX
	for (int x = 0; x < camW; ++x) {
		for (int y = 0; y < camH; ++y) {
			if (pix.getColor(x,y) != ofColor(0, 0, 0, 0)) {
				minX = x;
			}
		}
	}
	// get MaxX
	for (int x = camW-1; x >= 0; --x) {
		for (int y = 0; y < camH; ++y) {
			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
				maxX = x;
			}
		}
	}
	// get minY
	for (int y = 0; y < camH; ++y) {
		for (int x = 0; x < camW; ++x) {
			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
				minY = y;
			}
		}
	}
	// get maxY
	for (int y = camH-1; y >= 0; --y) {
		for (int x = 0; x < camW; ++x) {
			if (pix.getColor(x, y) != ofColor(0, 0, 0, 0)) {
				maxY = y;
			}
		}
	}
	// image that represents all drawn pixels from fbo
	ofImage img;
	img.allocate(maxX - minX, maxY - minY, OF_IMAGE_COLOR_ALPHA);
	pix.crop(minX, minY, maxX - minX, maxY - minY);
	img.setFromPixels(pix);
	return MovingImg(img, ofVec2f(img.getWidth() / 2, img.getHeight() / 2));
}

ofFbo Pen::getFbo() {
	drawing = false;
	return fbo;
}

// draw this FBO to main canvas
void Pen::drawFbo() {
	// if this is being drawn to, draw at origin
	if (drawing) {
		fbo.draw(0,0);
	}
	else {
		// otherwise draw at position specified
		fbo.draw(imgPos);
		// bounce ofscreen if image is moving too far from canvas
		if (imgPos.x > 2*camW || imgPos.x < -camW) {
			velocity = ofVec2f(velocity.x*-1, velocity.y);
		}
		if (imgPos.y > 2*camH || imgPos.y < -camH) {
			velocity = ofVec2f(velocity.x, velocity.y*-1);
		}
	}
}