#include "ofApp.h"
#include "ofxGuiGroupMinimal.h"
#include "ofxDynamixelParameter.h"
//--------------------------------------------------------------
void ofApp::setup(){

	param.set("bool param", true);
	
	gui.setup();
	
	auto g = new ofxGuiGroupMinimal();
	g->setup("group", "", 0, 0);
	g->add(new ofxGuiDXLToggle(param));
	gui.add(g);
	
	
	cout << typeid(bool).name() << endl;
	cout << sizeof(bool) << endl;
	
	cout << typeid(ofxDynamixel::dxlParameter<bool>*).name() << endl;
	
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
