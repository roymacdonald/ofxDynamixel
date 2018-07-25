//
//  ofxGuiGroupMinimal.cpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofxGuiGroupMinimal.h"
#include "ofxGuiGroup.h"
#include "ofxPanel.h"
#include "ofxSliderGroup.h"
#include "ofGraphics.h"
#include "ofxLabel.h"
#include "ofxInputField.h"

using namespace std;

ofxGuiGroupMinimal::ofxGuiGroupMinimal(){
	minimized = false;
//	spacing = 0;
//	spacingNextElement = 2;
	// header =  0 defaultHeight;
	bGuiActive = false;
}

ofxGuiGroupMinimal::ofxGuiGroupMinimal(const ofParameterGroup & parameters, const std::string& filename, float x, float y){
	minimized = false;
	parent = nullptr;
	setup(parameters, filename, x, y);
}

ofxGuiGroupMinimal * ofxGuiGroupMinimal::setup(const std::string& collectionName, const std::string& filename, float x, float y){
	ofParameterGroup parameters(collectionName);
	return setup(parameters, filename, x, y);
}

ofxGuiGroupMinimal * ofxGuiGroupMinimal::setup(const ofParameterGroup & _parameters, const std::string& _filename, float x, float y){
	b.x = x;
	b.y = y;
//	header = defaultHeight;
//	spacing = 0;
//	spacingNextElement = 2;
	if(parent != nullptr){
		b.width = parent->getWidth();
	}else{
		b.width = defaultWidth;
	}
	clear();
	filename = _filename;
	bGuiActive = false;
	
	for(std::size_t i = 0; i < _parameters.size(); i++){
		string type = _parameters.getType(i);
		if(type == typeid(ofParameter <int32_t> ).name()){
			auto p = _parameters.getInt(i);
			add(p);
		}else if(type == typeid(ofParameter <uint32_t> ).name()){
			auto p = _parameters.get<uint32_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <int64_t> ).name()){
			auto p = _parameters.get<int64_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <uint64_t> ).name()){
			auto p = _parameters.get<uint64_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <int8_t> ).name()){
			auto p = _parameters.get<int8_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <uint8_t> ).name()){
			auto p = _parameters.get<uint8_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <int16_t> ).name()){
			auto p = _parameters.get<int16_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <uint16_t> ).name()){
			auto p = _parameters.get<uint16_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <size_t> ).name()){
			auto p = _parameters.get<size_t>(i);
			add(p);
		}else if(type == typeid(ofParameter <float> ).name()){
			auto p = _parameters.getFloat(i);
			add(p);
		}else if(type == typeid(ofParameter <double> ).name()){
			auto p = _parameters.get<double>(i);
			add(p);
		}else if(type == typeid(ofParameter <bool> ).name()){
			auto p = _parameters.getBool(i);
			add(p);
		}else if(type == typeid(ofParameter <void> ).name()){
			auto p = _parameters.getVoid(i);
			add(p);
		}else if(type == typeid(ofParameter <ofDefaultVec2> ).name()){
			auto p = _parameters.getVec2f(i);
			add(p);
		}else if(type == typeid(ofParameter <ofDefaultVec3> ).name()){
			auto p = _parameters.getVec3f(i);
			add(p);
		}else if(type == typeid(ofParameter <ofDefaultVec4> ).name()){
			auto p = _parameters.getVec4f(i);
			add(p);
		}else if(type == typeid(ofParameter <ofColor> ).name()){
			auto p = _parameters.getColor(i);
			add(p);
		}else if(type == typeid(ofParameter <ofShortColor> ).name()){
			auto p = _parameters.getShortColor(i);
			add(p);
		}else if(type == typeid(ofParameter <ofFloatColor> ).name()){
			auto p = _parameters.getFloatColor(i);
			add(p);
		}else if(_parameters[i].valueType() == typeid(string).name()){
			if(_parameters[i].isReadOnly()){
				auto p = _parameters.get(i).castReadOnly<std::string, void>();
				add(p);
			}else{
				auto p = _parameters.getString(i);
				add(p);
			}
		}else if(type == typeid(ofParameterGroup).name()){
			auto p = _parameters.getGroup(i);
			ofxGuiGroupMinimal * panel = new ofxGuiGroupMinimal(p);
			add(panel);
		}else{
			ofLogWarning() << "ofxBaseGroup; no control for parameter of type " << type;
		}
	}
	
	parameters = _parameters;
	registerMouseEvents();
	
	setNeedsRedraw();
	
	return this;
}

void ofxGuiGroupMinimal::setWidthElements(float w){
	for(std::size_t i = 0; i < collection.size(); i++){
		collection[i]->setSize(w, collection[i]->getHeight());
		collection[i]->setPosition(b.x + b.width - w, collection[i]->getPosition().y);
		ofxGuiGroupMinimal * subgroup = dynamic_cast<ofxGuiGroupMinimal*>(collection[i]);
		if(subgroup != nullptr){
			subgroup->setWidthElements(w * .98);
		}
	}
	sizeChangedCB();
	setNeedsRedraw();
}

void ofxGuiGroupMinimal::add(ofxBaseGui * element){
	collection.push_back(element);
	
	element->setPosition(b.x, b.y + b.height  + spacing);
	
	b.height += element->getHeight() + spacing;
	
	//if(b.width<element->getWidth()) b.width = element->getWidth();
	
	element->unregisterMouseEvents();
	
	element->setParent(this);
	
	ofxGuiGroupMinimal * subgroup = dynamic_cast <ofxGuiGroupMinimal *>(element);
	if(subgroup != nullptr){
		subgroup->filename = filename;
		subgroup->setWidthElements(b.width * .98);
	}else{
		if(parent != nullptr){
			element->setSize(b.width * .98, element->getHeight());
			element->setPosition(b.x + b.width - element->getWidth(), element->getPosition().y);
		}
	}
	
	parameters.add(element->getParameter());
	setNeedsRedraw();
}

void ofxGuiGroupMinimal::add(const ofParameterGroup & parameters){
	ofxGuiGroupMinimal * panel = new ofxGuiGroupMinimal(parameters);
	add(panel);
}

void ofxGuiGroupMinimal::add(ofParameter <void> & parameter){
	add(new ofxButton(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <bool> & parameter){
	add(new ofxToggle(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <string> & parameter){
	add(new ofxInputField<std::string>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofVec2f> & parameter){
	add(new ofxVecSlider_ <ofVec2f>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofVec3f> & parameter){
	add(new ofxVecSlider_ <ofVec3f>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofVec4f> & parameter){
	add(new ofxVecSlider_ <ofVec4f>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <glm::vec2> & parameter){
	add(new ofxVecSlider_ <glm::vec2>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <glm::vec3> & parameter){
	add(new ofxVecSlider_ <glm::vec3>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <glm::vec4> & parameter){
	add(new ofxVecSlider_ <glm::vec4>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofColor> & parameter){
	add(new ofxColorSlider_ <unsigned char>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofShortColor> & parameter){
	add(new ofxColorSlider_ <unsigned short>(parameter, b.width));
}

void ofxGuiGroupMinimal::add(ofParameter <ofFloatColor> & parameter){
	add(new ofxColorSlider_ <float>(parameter, b.width));
}

void ofxGuiGroupMinimal::clear(){
	collection.clear();
	parameters.clear();
	b.height =  spacing + spacingNextElement;
	sizeChangedCB();
}

bool ofxGuiGroupMinimal::mouseMoved(ofMouseEventArgs & args){
	ofMouseEventArgs a = args;
	for(std::size_t i = 0; i < collection.size(); i++){
		if(collection[i]->mouseMoved(a)){
			return true;
		}
	}
	if(isGuiDrawing() && b.inside(ofPoint(args.x, args.y))){
		return true;
	}else{
		return false;
	}
}

bool ofxGuiGroupMinimal::mousePressed(ofMouseEventArgs & args){
	if(setValue(args.x, args.y, true)){
		return true;
	}
	auto attended = false;
	ofMouseEventArgs a = args;
	for(std::size_t i = 0; i < collection.size(); i++){
		if(collection[i]->mousePressed(a)){
			attended = true;
		}
	}
	return attended;
}

bool ofxGuiGroupMinimal::mouseDragged(ofMouseEventArgs & args){
	if(setValue(args.x, args.y, false)){
		return true;
	}
	if(bGuiActive){
		ofMouseEventArgs a = args;
		for(std::size_t i = 0; i < collection.size(); i++){
			if(collection[i]->mouseDragged(a)){
				return true;
			}
		}
	}
	return false;
}

bool ofxGuiGroupMinimal::mouseReleased(ofMouseEventArgs & args){
	bGuiActive = false;
	for(std::size_t k = 0; k < collection.size(); k++){
		ofMouseEventArgs a = args;
		if(collection[k]->mouseReleased(a)){
			return true;
		}
	}
	if(isGuiDrawing() && b.inside(ofPoint(args.x, args.y))){
		return true;
	}else{
		return false;
	}
}

bool ofxGuiGroupMinimal::mouseScrolled(ofMouseEventArgs & args){
	ofMouseEventArgs a = args;
	for(std::size_t i = 0; i < collection.size(); i++){
		if(collection[i]->mouseScrolled(a)){
			return true;
		}
	}
	if(isGuiDrawing() && b.inside(ofPoint(args.x, args.y))){
		return true;
	}else{
		return false;
	}
}

void ofxGuiGroupMinimal::generateDraw(){
	border.clear();
	border.setFillColor(ofColor(thisBorderColor, 180));
	border.setFilled(true);
	border.rectangle(b.x, b.y + spacingNextElement, b.width + 1, b.height);
	
//	
//	headerBg.clear();
//	headerBg.setFillColor(thisHeaderBackgroundColor);
//	headerBg.setFilled(true);
//	headerBg.rectangle(b.x, b.y + 1 + spacingNextElement, b.width, header);
//	
//	textMesh = getTextMesh(getName(), textPadding + b.x, header / 2 + 4 + b.y + spacingNextElement);
//	if(minimized){
//		textMesh.append(getTextMesh("+", b.width - textPadding - 8 + b.x, header / 2 + 4 + b.y + spacingNextElement));
//	}else{
//		textMesh.append(getTextMesh("-", b.width - textPadding - 8 + b.x, header / 2 + 4 + b.y + spacingNextElement));
//	}
}

void ofxGuiGroupMinimal::render(){
	border.draw();
//	headerBg.draw();
	
	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode != OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
	ofColor c = ofGetStyle().color;
///	ofSetColor(thisTextColor);
//	
//	bindFontTexture();
//	textMesh.draw();
//	unbindFontTexture();
	
	if(!minimized){
		for(std::size_t i = 0; i < collection.size(); i++){
			collection[i]->draw();
		}
	}
	
	ofSetColor(c);
	if(blendMode != OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}

vector <string> ofxGuiGroupMinimal::getControlNames() const{
	vector <string> names;
	for(std::size_t i = 0; i < collection.size(); i++){
		names.push_back(collection[i]->getName());
	}
	return names;
}

ofxIntSlider & ofxGuiGroupMinimal::getIntSlider(const std::string& name){
	return getControlType <ofxIntSlider>(name);
}

ofxFloatSlider & ofxGuiGroupMinimal::getFloatSlider(const std::string& name){
	return getControlType <ofxFloatSlider>(name);
}

ofxToggle & ofxGuiGroupMinimal::getToggle(const std::string& name){
	return getControlType <ofxToggle>(name);
}

ofxButton & ofxGuiGroupMinimal::getButton(const std::string& name){
	return getControlType <ofxButton>(name);
}

ofxGuiGroupMinimal & ofxGuiGroupMinimal::getGroup(const std::string& name){
	return getControlType <ofxGuiGroupMinimal>(name);
}

ofxBaseGui * ofxGuiGroupMinimal::getControl(const std::string& name){
	for(std::size_t i = 0; i < collection.size(); i++){
		if(collection[i]->getName() == name){
			return collection[i];
		}
	}
	return nullptr;
}

bool ofxGuiGroupMinimal::setValue(float mx, float my, bool bCheck){
	
	if(!isGuiDrawing()){
		bGuiActive = false;
		return false;
	}
	
	
	if(bCheck){
		if(b.inside(mx, my)){
			bGuiActive = true;
//			
//			ofRectangle minButton(b.x, b.y, b.width, header);
//			if(minButton.inside(mx, my)){
//				minimized = !minimized;
//				if(minimized){
//					minimize();
//				}else{
//					maximize();
//				}
//				return true;
//			}
		}
	}
	
	return false;
}

void ofxGuiGroupMinimal::minimize(){
	minimized = true;
	b.height = spacing + spacingNextElement + 1 /*border*/;
	if(parent){
		parent->sizeChangedCB();
	}
	setNeedsRedraw();
	onMinimize();
}

void ofxGuiGroupMinimal::maximize(){
	minimized = false;
	for(std::size_t i = 0; i < collection.size(); i++){
		b.height += collection[i]->getHeight() + spacing;
	}
	if(parent){
		parent->sizeChangedCB();
	}
	setNeedsRedraw();
	onMaximize();
}

void ofxGuiGroupMinimal::minimizeAll(){
	for(std::size_t i = 0; i < collection.size(); i++){
		ofxGuiGroupMinimal * group = dynamic_cast <ofxGuiGroupMinimal *>(collection[i]);
		if(group){
			group->minimize();
		}
	}
}

void ofxGuiGroupMinimal::maximizeAll(){
	for(std::size_t i = 0; i < collection.size(); i++){
		ofxGuiGroupMinimal * group = dynamic_cast <ofxGuiGroupMinimal *>(collection[i]);
		if(group){
			group->maximize();
		}
	}
}

bool ofxGuiGroupMinimal::isMinimized() const{
	return minimized;
}

void ofxGuiGroupMinimal::onMinimize(){
	
}

void ofxGuiGroupMinimal::onMaximize(){
	
}

void ofxGuiGroupMinimal::sizeChangedCB(){
	float y;
	if(parent){
		y = b.y  + spacing + spacingNextElement;
	}else{
		y = b.y  + spacing;
	}
	for(std::size_t i = 0; i < collection.size(); i++){
		collection[i]->setPosition(collection[i]->getPosition().x, y + spacing);
		y += collection[i]->getHeight() + spacing;
	}
	if(minimized){
		b.height =  spacing + spacingNextElement + 1 /*border*/;
	}else{
		b.height = y - b.y;
	}
	if(parent){
		parent->sizeChangedCB();
	}
	setNeedsRedraw();
}

std::size_t ofxGuiGroupMinimal::getNumControls() const {
	return collection.size();
}

ofxBaseGui * ofxGuiGroupMinimal::getControl(std::size_t num){
	if(num < collection.size()){
		return collection[num];
	}else{
		return nullptr;
	}
}

ofAbstractParameter & ofxGuiGroupMinimal::getParameter(){
	return parameters;
}

void ofxGuiGroupMinimal::setPosition(const ofPoint& p){
	ofVec2f diff = p - b.getPosition();
	
	for(std::size_t i = 0; i < collection.size(); i++){
		collection[i]->setPosition(collection[i]->getPosition() + diff);
	}
	
	b.setPosition(p);
	setNeedsRedraw();
}

void ofxGuiGroupMinimal::setPosition(float x, float y){
	setPosition(ofVec2f(x, y));
}

