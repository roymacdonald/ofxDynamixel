//
//  ofxGuiGroupMinimal.hpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#pragma once

//#include "ofxGuiGroup.h"


//class ofxGuiGroupMinimal : public ofxGuiGroup{
//public:
//	ofxGuiGroupMinimal();
//	
//	ofxGuiGroup * setup(const ofParameterGroup & _parameters, const std::string& _filename, float x, float y) ;
//	float getHeader(){return header;}
////	virtual bool mouseMoved(ofMouseEventArgs & args) override{return false;}
////	virtual bool mousePressed(ofMouseEventArgs & args) override{return false;}
////	virtual bool mouseDragged(ofMouseEventArgs & args) override{return false;}
////	virtual bool mouseReleased(ofMouseEventArgs & args) override{return false;}
////	virtual bool mouseScrolled(ofMouseEventArgs & args) override{return false;}
//
//protected:
//	virtual void generateDraw() override;
//	virtual void render() override;
//	
//	
//}; #pragma once
#include "ofxBaseGui.h"

#include "ofxSlider.h"
#include "ofxButton.h"
#include "ofxLabel.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"

class ofxGuiGroupMinimal : public ofxBaseGui {
public:
	ofxGuiGroupMinimal();
	ofxGuiGroupMinimal(const ofParameterGroup & parameters, const std::string& _filename = "settings.xml", float x = 10, float y = 10);
	virtual ~ofxGuiGroupMinimal(){
	}
	ofxGuiGroupMinimal * setup(const std::string& collectionName = "", const std::string& filename = "settings.xml", float x = 10, float y = 10);
	ofxGuiGroupMinimal * setup(const ofParameterGroup & parameters, const std::string& filename = "settings.xml", float x = 10, float y = 10);
	
	void add(ofxBaseGui * element);
	void add(const ofParameterGroup & parameters);
	
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type add(ofParameter<T> & p){
		add(new ofxSlider<T>(p));
	}
	void add(ofParameter <void> & parameter);
	void add(ofParameter <bool> & parameter);
	void add(ofParameter <std::string> & parameter);
	
	template<typename F>
	void add(ofReadOnlyParameter <std::string, F> & parameter){
		add(new ofxLabel(parameter));
	}
	void add(ofParameter <ofVec2f> & parameter);
	void add(ofParameter <ofVec3f> & parameter);
	void add(ofParameter <ofVec4f> & parameter);
	void add(ofParameter <glm::vec2> & parameter);
	void add(ofParameter <glm::vec3> & parameter);
	void add(ofParameter <glm::vec4> & parameter);
	void add(ofParameter <ofColor> & parameter);
	void add(ofParameter <ofShortColor> & parameter);
	void add(ofParameter <ofFloatColor> & parameter);
	
	void minimize();
	void maximize();
	void minimizeAll();
	void maximizeAll();
	bool isMinimized() const;
	
	void setWidthElements(float w);
	
	void clear();
	
	virtual void sizeChangedCB();
	
	virtual bool mouseMoved(ofMouseEventArgs & args);
	virtual bool mousePressed(ofMouseEventArgs & args);
	virtual bool mouseDragged(ofMouseEventArgs & args);
	virtual bool mouseReleased(ofMouseEventArgs & args);
	virtual bool mouseScrolled(ofMouseEventArgs & args);
	
	
	std::vector <std::string> getControlNames() const;
	std::size_t getNumControls() const;
	
	ofxIntSlider & getIntSlider(const std::string& name);
	ofxFloatSlider & getFloatSlider(const std::string& name);
	ofxToggle & getToggle(const std::string& name);
	ofxButton & getButton(const std::string& name);
	ofxGuiGroupMinimal & getGroup(const std::string& name);
	
	ofxBaseGui * getControl(const std::string& name);
	ofxBaseGui * getControl(std::size_t num);
	
	virtual ofAbstractParameter & getParameter();
	
	virtual void setPosition(const ofPoint& p);
	virtual void setPosition(float x, float y);
protected:
	virtual void render();
	virtual bool setValue(float mx, float my, bool bCheck);
	virtual void onMinimize();
	virtual void onMaximize();
	
	float spacing = 0;
	float spacingNextElement = 1;
//	float header;
	
	template <class ControlType>
	ControlType & getControlType(const std::string& name);
	
	virtual void generateDraw();
	
	std::vector <ofxBaseGui *> collection;
	ofParameterGroup parameters;
	
	std::string filename;
	bool minimized;
	bool bGuiActive;
	
	ofPath border, headerBg;
	ofVboMesh textMesh;
};

template <class ControlType>
ControlType & ofxGuiGroupMinimal::getControlType(const std::string& name){
	ControlType * control = dynamic_cast <ControlType *>(getControl(name));
	if(control){
		return *control;
	}else{
		ofLogWarning() << "getControlType " << name << " not found, creating new";
		control = new ControlType;
		control->setName(name);
		add(control);
		return *control;
	}
}
