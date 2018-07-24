#include "ofApp.h"


using namespace ofxDynamixel;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//gui.setup();
	
	connection = make_shared<Connection>("/dev/tty.usbmodem1421", 2, 57600);
	if(connection->open()){
		cout << "connection opened!" << endl;
	}else{
		cout << "connection failed to opened!" << endl;
	}
	
	
	servos.resize(4);
	for(int i =0 ; i < servos.size(); i++){
		servos[i] = make_shared<ofxDynamixel::ServoGuiXL320>(); 
		servos[i]->setup(i+1, connection);
		servos[i]->setTorqueEnabled(true);
		//gui.add(servos[i]->parameters);
	}
	for(int i =1 ; i < servos.size(); i++){
		auto s = servos[i -1]->panel.getShape();
		servos[i]->panel.setPosition( s.getMaxX() + 10, s.y);
	}
//	params.setup();
//	gui.add(params.parameters);
}

//--------------------------------------------------------------
void ofApp::update() {
	for(auto& s: servos){
//		s->updateCurrentSpeed();
//		s->updateCurrentPosition();
		s->update();
	}			
}

//--------------------------------------------------------------
void ofApp::draw() {

	
	for(auto& s: servos){
		s->panel.draw();
	}	
	
//	gui.draw();
	stringstream ss;
//	ss << "positions:\n";
//	for(int i =0 ; i < servos.size(); i++){
//		ss << servos[i]->presentPosition() << endl; 
//	}
	ss << "INDEX: " << index << endl;	
	ofDrawBitmapString(ss.str(), 20, ofGetHeight() - 100);
	if(!fullReport.empty()){
		ofDrawBitmapStringHighlight(fullReport, 300, 30);
	
	}
}
//--------------------------------------------------------------
void ofApp::exit(){
	cout << __PRETTY_FUNCTION__ << endl;
	for(int i =0 ; i < servos.size(); i++){
		servos[i]->setTorqueEnabled(false);
	}
	connection->closePort();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == OF_KEY_LEFT){
//		servos[index]->position--;
	}else if(key == OF_KEY_RIGHT){
//		servos[index]->position++;
	}else if(key == OF_KEY_UP){
		(++index)%= servos.size();
	}else if(key == OF_KEY_DOWN){
		(--index)%= servos.size();
	}else if(key == '1' || key == '2'){
		int r = (int)ofRandom(1024);
		servos[key - '1']->setGoalPosition(r);
		cout << r <<endl;
	}else if(key == ' '){
		
		fullReport = "";
		for(auto&s: servos){
//			fullReport += s->getFullReportString();
			fullReport += "----------------------------\n";
		}
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
