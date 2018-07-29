//
//  ofxGuiDXLToggle.cpp
//  example
//
//  Created by Roy Macdonald on 7/28/18.
//
//

#include "ofxGuiDXLToggle.h"

#include "ofGraphics.h"
using namespace std;

ofxGuiDXLToggle::ofxGuiDXLToggle(ofParameter<bool> _bVal, float width, float height){
	setup(_bVal,width,height);
}

//ofxGuiDXLToggle::~ofxGuiDXLToggle(){
////	value.removeListener(this,&ofxGuiDXLToggle::valueChanged);
//}

ofxGuiDXLToggle * ofxGuiDXLToggle::setup(ofParameter<bool> _bVal, float width, float height){
	ofxToggle::setup(_bVal, width, height);
	checkboxRect.set(1, 1, b.height - 2, b.height - 2);
	
	setNeedsRedraw();
	
	return this;
	
}

ofxGuiDXLToggle * ofxGuiDXLToggle::setup(const std::string& toggleName, bool _bVal, float width, float height){
	value.set(toggleName,_bVal);
	return setup(value,width,height);
}

void ofxGuiDXLToggle::generateDraw(){
	bg.clear();
	bg.setFillColor(thisBackgroundColor);
	bg.rectangle(b);
	
	fg.clear();
	if(value){
		fg.setFilled(true);
		fg.setFillColor(thisFillColor);
	}else{
		fg.setFilled(false);
		fg.setStrokeWidth(1);
		fg.setStrokeColor(thisFillColor);
	}
	fg.rectangle(b);
	
	std::string name;
	auto textX = b.x + textPadding ;
	if(getTextBoundingBox(getName(), textX, 0).getMaxX() > b.getMaxX() - textPadding){
		for(auto c: ofUTF8Iterator(getName())){
			auto next = name;
			ofUTF8Append(next, c);
			if(getTextBoundingBox(next,textX,0).getMaxX() > b.getMaxX() - textPadding){
				break;
			}else{
				name = next;
			}
		}
	}else{
		name = getName();
	}
	
	textMesh = getTextMesh(name, textX, b.y+b.height / 2 + 4);
}

void ofxGuiDXLToggle::render(){
	bg.draw();
	fg.draw();
	
//	if( value ){
////		if(
////		cross.draw();
//	}
	
	ofColor c = ofGetStyle().color;
	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
	ofSetColor(thisTextColor);
	
	bindFontTexture();
	textMesh.draw();
	unbindFontTexture();
	
	ofSetColor(c);
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}


bool ofxGuiDXLToggle::setValue(float mx, float my, bool bCheck){
	
	if( !isGuiDrawing() ){
		bGuiActive = false;
		return false;
	}
	if( bCheck ){
//		ofRectangle checkRect = checkboxRect;
//		checkRect.x += b.x;
//		checkRect.y += b.y;
		
		if( b.inside(mx, my) ){
			bGuiActive = true;
		}else{
			bGuiActive = false;	
		}
	}
	if( bGuiActive ){
		value = !value;
		return true;
	}
	return false;
}

