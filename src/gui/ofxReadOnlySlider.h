//
//  ofxReadOnlySlider.hpp
//  example
//
//  Created by Roy Macdonald on 7/25/18.
//
//

#pragma once
#include "ofxSlider.h"
#include "ofxBaseGui.h"
#include "ofParameter.h"
#include "ofxInputField.h"

template<typename Type>
class ofxReadOnlySlider: public ofxSlider<Type>{
	friend class ofxPanel;
public:
	
	ofxReadOnlySlider<Type>();

	ofxReadOnlySlider<Type>(ofParameter<Type> _val, float width = 200, float height = 9);
	ofxReadOnlySlider* setup(ofParameter<Type> _val, float width = 200, float height = 9);
	ofxReadOnlySlider* setup(const std::string& sliderName, Type _val, Type _min, Type _max, float width = 200, float height = 9);

	
	
	virtual bool mouseMoved(ofMouseEventArgs & args){return false;}
	virtual bool mousePressed(ofMouseEventArgs & args){return false;}
	virtual bool mouseDragged(ofMouseEventArgs & args){return false;}
	virtual bool mouseReleased(ofMouseEventArgs & args){return false;}
	virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}
	void setShowName(bool showName);
	void showName(){setShowName(true);}
	void hideName(){setShowName(false);}
	bool isShowingName(){return bShowName;}
protected:
	bool bShowName = false;
	virtual void generateText();
	
};
