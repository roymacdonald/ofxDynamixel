#include "ofApp.h"
#include "ofxGui.h"

using namespace ofxDynamixel;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	
	
//	ofTrueTypeFontSettings fontSettings("uni 05_53", 5);
	
//	ofxGuiSetFont(fontSettings); 
	//gui.setup();
	
	connection = make_shared<Connection>("/dev/tty.usbmodem1421", 2, 57600);
	if(connection->open()){
		cout << "connection opened!" << endl;
	}else{
		cout << "connection failed to opened!" << endl;
	}
	
	
	servos.resize(1);
	for(int i =0 ; i < servos.size(); i++){
		servos[i] = make_shared<Servo<XL320>>(i+1, connection); 
//		servos[i]->setup(i+1, connection);
		servos[i]->createGui();
		servos[i]->setTorqueEnabled(true);
		//gui.add(servos[i]->parameters);
	}
	
	for(int i =1 ; i < servos.size(); i++){
		auto s = servos[i -1]->gui->panel.getShape();
		servos[i]->gui->panel.setPosition( s.getMaxX() + 10, s.y);
	}
	for(auto& s: servos){
		s->gui->updateEeprom();
	}
//	params.setup();
//	gui.add(params.parameters);
}

//--------------------------------------------------------------
void ofApp::update() {
	
	for(auto& s: servos){
////		s->updateCurrentSpeed();
////		s->updateCurrentPosition();
		s->gui->update();
	}			
}

//--------------------------------------------------------------
void ofApp::draw() {

	
	for(auto& s: servos){
		s->gui->panel.draw();
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
//		servos[0]->P_goalPosition.writeParam--;
	}else if(key == OF_KEY_RIGHT){
//		servos[0]->P_goalPosition.writeParam++;
	}else if(key == OF_KEY_UP){
		(++index)%= servos.size();
	}else if(key == OF_KEY_DOWN){
		(--index)%= servos.size();
	}else if(key == '1' || key == '2'){
		int r = (int)ofRandom(1024);
		servos[key - '1']->setGoalPosition(r);
		cout << r <<endl;
	}else if(key == 'm'){
		for(auto& s: servos){
			cout << "Servo  " << s->getId() << " model: " << s->getModelNumber() << endl;
		}
	}else if(key == 'p'){
		for(auto& s: servos){
			if(!s->ping()){
				cout << "ping failed " << s->getId() << endl;
			}
		}
	}else if(key == ' '){
		for(auto& s: servos){
			//		s->updateCurrentSpeed();
			//		s->updateCurrentPosition();
			s->setGoalPosition((uint16_t)floor(ofRandom(0, 1023)));
//			s->update();
		}
//		fullReport = "";
//		for(auto&s: servos){
////			fullReport += s->getFullReportString();
//			fullReport += "----------------------------\n";
//		}
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
