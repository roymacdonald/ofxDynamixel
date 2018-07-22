#include "ofApp.h"


using namespace ofxDynamixel;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	gui.setup();
	
	connection = make_shared<Connection>("/dev/tty.usbmodem1411", 2, 57600);
	if(connection->open()){
		cout << "connection opened!" << endl;
	}else{
		cout << "connection failed to opened!" << endl;
	}
	
	
	servos.resize(2);
	for(int i =0 ; i < servos.size(); i++){
		servos[i] = make_shared<ofxDynamixel::Servo>(); 
		servos[i]->setup(i+1, connection);
		gui.add(servos[i]->parameters);
	}
	
	
	

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();
	stringstream ss;
	ss << "positions:\n";
	for(int i =0 ; i < servos.size(); i++){
		ss << servos[i]->presentPosition() << endl; 
	}
	ofDrawBitmapString(ss.str(), 20, ofGetHeight() - 100);
}
//--------------------------------------------------------------
void ofApp::exit(){
	cout << __PRETTY_FUNCTION__ << endl;
	connection->closePort();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == '1' || key == '2'){
		int r = (int)ofRandom(1024);
		servos[key - '1']->setGoalPosition(r);
		cout << r <<endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
