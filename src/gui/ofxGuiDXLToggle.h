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

	ofxGuiDXLToggle(ofParameter<bool> _bVal, bool bShowName, bool bIsReadOnly, float width = defaultWidth, float height = defaultHeight );
	ofxGuiDXLToggle * setup(ofParameter<bool> _bVal, bool bShowName, bool bIsReadOnly, float width = defaultWidth, float height = defaultHeight);
	ofxGuiDXLToggle * setup(const std::string& toggleName, bool _bVal, bool bShowName, bool bIsReadOnly, float width = defaultWidth, float height = defaultHeight);
	
		
protected:
	virtual void render();	
	bool setValue(float mx, float my, bool bCheck);
	void generateDraw();
	bool bShowName = true;
	bool bIsReadOnly = false;

};
