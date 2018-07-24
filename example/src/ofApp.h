#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxDynamixel.h"
#include "ofxDynamixelServo.h"

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
	vector< shared_ptr<ofxDynamixel::ServoGuiXL320> > servos;

	//ofxPanel gui;
	
	string fullReport;
	
	size_t index;
		
//	ofxDynamixel::ServoGuiXL320 params;

};
