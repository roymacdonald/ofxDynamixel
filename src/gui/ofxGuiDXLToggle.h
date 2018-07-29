//
//  ofxGuiDXLToggle.h
//  example
//
//  Created by Roy Macdonald on 7/28/18.
//
//

#pragma once

#include "ofParameter.h"
#include "ofxToggle.h"

class ofxGuiDXLToggle : public ofxToggle{
public:
	ofxGuiDXLToggle(){};
//	~ofxGuiDXLToggle();
	ofxGuiDXLToggle(ofParameter<bool> _bVal, float width = defaultWidth, float height = defaultHeight);
	ofxGuiDXLToggle * setup(ofParameter<bool> _bVal, float width = defaultWidth, float height = defaultHeight);
	ofxGuiDXLToggle * setup(const std::string& toggleName, bool _bVal, float width = defaultWidth, float height = defaultHeight);
	
	
//	virtual bool mouseMoved(ofMouseEventArgs & args);
//	virtual bool mousePressed(ofMouseEventArgs & args);
//	virtual bool mouseDragged(ofMouseEventArgs & args);
//	virtual bool mouseReleased(ofMouseEventArgs & args);
//	virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}
//	
	
//	template<class ListenerClass, typename ListenerMethod>
//	void addListener(ListenerClass * listener, ListenerMethod method){
//		value.addListener(listener,method);
//	}
//	
//	template<class ListenerClass, typename ListenerMethod>
//	void removeListener(ListenerClass * listener, ListenerMethod method){
//		value.removeListener(listener,method);
//	}
//	
//	bool operator=(bool v);
//	operator const bool & ();
//	
//	virtual ofAbstractParameter & getParameter();
	
protected:
	virtual void render();
//	ofRectangle checkboxRect;
//	ofParameter<bool> value;
//	bool bGuiActive;
	
	bool setValue(float mx, float my, bool bCheck);
	void generateDraw();
//	void valueChanged(bool & value);
//	ofPath bg,fg,cross;
//	ofVboMesh textMesh;
};
