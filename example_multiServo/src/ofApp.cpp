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
	
	//-------------- SyncGroup setup start -------------------------
	// The dynamixel SDK allows to send and retrieve the same parameter from several servos in a single call, for which the SyncGroup is used.
	// It is a lot more efficient than doing a for loop on the servos and reading a parameter for all of these.
	// In this case we will read the "present Position", which is probably the most useful of all.
	// the string passed in the following function is the parameter we want to sync-read.
	// The available strings to be passed are the names of the parameters the servo has. 
	// You can find out which are the strings for the other parameters by looking at ofxDynamixel/src/Servos/ofxDynamixelXL430.cpp (or which ever other model you are using).
	
	positionReadSyncGroup.setup("presentPosition", connection);
	//-------------- SyncGroup setup  end -------------------------
	
	
	//-------------- Servo setup start -------------------------
	vector<uint8_t> servoIds = {1, 2, 3, 10};// put here all your servos IDs. It does not matter if these are not consecutive.
	
	servos.resize(servoIds.size());
	
	
	float guiMargin = 10;
	
	float guiPanelWidth = (ofGetWidth() - guiMargin*float(servoIds.size()) )/float(servoIds.size());
	
	for(int i =0 ; i < servos.size(); i++){
		
		servos[i] = make_shared<Servo<XL430>>(servoIds[i], // this is the servo's ID.  
											  connection);// we pass the connection we just created to this servo
		
		
		servos[i]->createGui(guiPanelWidth); // this is optional. it is not necesary to create a gui. you can controll everything prograatically without a gui.
		servos[i]->setTorqueEnabled(true); // you need to enable torque in order to move the servo.
		servos[i]->updateAllParamsFromServo(); // this will update the gui/parameters so these reflect the servo's current state.
		
		positionReadSyncGroup.addServoToSync(servos[i]); // we add the newly created servo to the sync group.
		
	}
	//-------------- Servo setup end -------------------------
	
	
	
	for(int i =1 ; i < servos.size(); i++){
		auto s = servos[i -1]->gui->panel.getShape();
		servos[i]->gui->panel.setPosition( s.getMaxX() + guiMargin, s.y);
	}

}

//--------------------------------------------------------------
void ofApp::update() {
	
	positionReadSyncGroup.sync();// this will update the syncReadGroup
}

//--------------------------------------------------------------
void ofApp::draw() {
		
	stringstream ss;
	ss << "Press the following keys:\n";
	ss << "m              :  print servo ID and model number" << endl;
	ss << "p              :  ping servo" << endl;
	ss << "[space bar]    :  set resevo to random position" << endl;
	ss << "u              :  update the gui with the servo's eeprom (non-volatile) parameters" << endl;
	
	ofBitmapFont bf;
	auto bb = bf.getBoundingBox(ss.str(), 0,0);
	
	ofDrawBitmapStringHighlight(ss.str(), ofGetWidth() - bb.width - 20, ofGetHeight() - bb.height - 20);
	
	
	for(auto& s: servos){
		s->drawGui();
	}	
}
//--------------------------------------------------------------
void ofApp::exit(){
	for(int i =0 ; i < servos.size(); i++){
		servos[i]->setTorqueEnabled(false);
	}
	connection->closePort();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(key == 'm'){
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
			s->setGoalPosition((uint16_t)floor(ofRandom(0, s->model.getResolution())));
		}
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
