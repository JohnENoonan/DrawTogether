#include "movingImg.h"

MovingImg::MovingImg(){

}

MovingImg::MovingImg(ofImage image, ofVec2f position) {
	img = image;
	pos = position;
	velocity = ofVec2f(ofRandom(-1 * MAX_VEL, MAX_VEL), ofRandom(-1 * MAX_VEL, MAX_VEL));
	alpha = ofRandom(MIN_ALPHA, MAX_ALPHA);
}

void MovingImg::update() {
	pos = pos + velocity;
	
}

