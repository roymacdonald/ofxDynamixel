#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxDynamixel.h"
#include "ofxDynamixelServo.h"

#include "ofxDynamixelXL430.h"// remember to include the servo model that you are using


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	
	void exit();
	
	shared_ptr<ofxDynamixel::Connection> connection;
	shared_ptr<ofxDynamixel::Servo<ofxDynamixel::XL430> > servo;
	
	string fullReport;
	

};
