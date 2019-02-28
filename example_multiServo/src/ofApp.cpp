#include "ofApp.h"
#include "ofxGui.h"

using namespace ofxDynamixel;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	//-------------- Connection setup start -------------------------
	// you only need to create one connection per app, which is shared for all the servos.
	// It needs to be a shared_ptr and not a regularly instanced object.
	
	connection = make_shared<Connection>("/dev/tty.usbmodem1421"// Make sure you put here the right port for your interface
										 , 2 // Dynamixel protocol version. can be either 1 or 2
										 , 57600); // serial baud rate. 57600 is dynamixel's default. It depends on your servos and interface how much you can increase it 
	if(connection->open()){
		cout << "connection opened!" << endl;
	}else{
		cout << "connection failed to opened!" << endl;
	}
	
	//-------------- Connection setup end -------------------------
	
	servos.resize(1);
	for(int i =0 ; i < servos.size(); i++){
		servos[i] = make_shared<Servo<XL430>>(4, connection); 
//		servos[i]->setup(i+1, connection);
		servos[i]->createGui();
		servos[i]->setTorqueEnabled(true);
		servos[i]->updateAllParamsFromServo();
		//gui.add(servos[i]->parameters);
	}
	
	
	
//	for(int i =1 ; i < servos.size(); i++){
//		auto s = servos[i -1]->gui->panel.getShape();
//		servos[i]->gui->panel.setPosition( s.getMaxX() + 10, s.y);
//	}
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
//		s->gui->update();
		s->readDataTo(s->model.presentPosition);
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
}
//--------------------------------------------------------------
void ofApp::exit(){
//	cout << __PRETTY_FUNCTION__ << endl;
	for(int i =0 ; i < servos.size(); i++){
		servos[i]->setTorqueEnabled(false);
	}
	connection->closePort();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == OF_KEY_LEFT){
		servos[0]->model.goalPosition.W_value --;// P_goalPosition.writeParam--;
	}else if(key == OF_KEY_RIGHT){
		servos[0]->model.goalPosition.W_value ++;//->P_goalPosition.writeParam++;
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
			s->setGoalPosition((uint16_t)floor(ofRandom(0, 1023)));
		}
		
//		servos[0]->setId(3);
		
	}else if(key == 'u'){
		for(auto& s: servos){
			s->gui->updateEeprom();
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
