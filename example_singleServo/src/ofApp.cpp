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
	
	//-------------- Servo setup start -------------------------
		servo = make_shared<Servo<XL430>>(4, // this is the servo's ID.
										  connection);// we pass the connection we just created to this servo
		
		servo->createGui(); // it is not necesary to create a gui. you can controll everything prograatically without a gui.
		servo->setTorqueEnabled(true); // you need to enable torque in order to move the servo.
		servo->updateAllParamsFromServo(); // this will update the gui/parameters so these reflect the servo's current state.
	//-------------- Servo setup end -------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
	
	// The following updates the present position parameter so it will reflect the servos present position.
	// This can make you app to run slower so use with caution.
	// if you want to use more than one servo look at the multi servo example
	servo->updatePresentPosition();
				
}

//--------------------------------------------------------------
void ofApp::draw() {
	servo->drawGui();

	stringstream ss;
	ss << "Press the following keys:\n";
	ss << "Left arrow key : decrement servo position by one step" <<endl;
	ss << "Right arrow key: increment servo position by one step" <<endl;
	ss << "m              :  print servo ID and model number" << endl;
	ss << "p              :  ping servo" << endl;
	ss << "[space bar]    :  set resevo to random position" << endl;
	ss << "u              :  update the gui with the servo's eeprom (non-volatile) parameters" << endl;
	
	ofBitmapFont bf;
	auto bb = bf.getBoundingBox(ss.str(), 0,0);
	
	ofDrawBitmapStringHighlight(ss.str(), ofGetWidth() - bb.width - 20, ofGetHeight() - bb.height - 20);
	
}
//--------------------------------------------------------------
void ofApp::exit(){

	// just make sure to disengage the servo on the app's exit
	servo->setTorqueEnabled(false);
	
	connection->closePort();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == OF_KEY_LEFT){
		servo->model.goalPosition.W_value --;
	}else if(key == OF_KEY_RIGHT){
		servo->model.goalPosition.W_value ++;
	}else if(key == OF_KEY_UP){
		
	}else if(key == OF_KEY_DOWN){
		
	}else if(key == 'm'){
		cout << "Servo  " << servo->getId() << " model: " << servo->getModelNumber() << endl;
	}else if(key == 'p'){
		if(!servo->ping()){
			cout << "ping failed " << servo->getId() << endl;
		}
	}else if(key == ' '){
		servo->setGoalPosition((uint16_t)floor(ofRandom(0, servo->model.getResolution())));
	}else if(key == 'u'){
		servo->gui->updateEeprom();
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
