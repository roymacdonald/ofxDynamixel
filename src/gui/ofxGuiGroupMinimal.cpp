//
//  ofxGuiGroupMinimal.cpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofxGuiGroupMinimal.h"

ofxGuiGroupMinimal::ofxGuiGroupMinimal(){
	minimized = false;
	spacing = 1;
	spacingNextElement = 3;
	header = 0;
	bGuiActive = false;
}
ofxGuiGroup * ofxGuiGroupMinimal::setup(const ofParameterGroup & _parameters, const std::string& _filename, float x, float y){
	ofxGuiGroup::setup(_parameters, _filename, x, y);
	header = 0;
	setNeedsRedraw();
	return this;
}
void ofxGuiGroupMinimal::generateDraw(){
	border.clear();
	border.setFillColor(ofColor(thisBorderColor, 180));
	border.setFilled(true);
	border.rectangle(b.x, b.y + spacingNextElement, b.width + 1, b.height);
	
	
	headerBg.clear();
	
	textMesh.clear();
//	= getTextMesh(getName(), textPadding + b.x, header / 2 + 4 + b.y + spacingNextElement);
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
//	ofSetColor(thisTextColor);
//	
//	bindFontTexture();
//	textMesh.draw();
//	unbindFontTexture();
//	
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
