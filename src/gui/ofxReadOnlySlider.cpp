//
//  ofxReadOnlySlider.cpp
//  example
//
//  Created by Roy Macdonald on 7/25/18.
//
//

#include "ofxReadOnlySlider.h"


template<typename Type>
ofxReadOnlySlider<Type>::ofxReadOnlySlider():ofxSlider<Type>(){}



template<typename Type>
ofxReadOnlySlider<Type>::ofxReadOnlySlider(ofParameter<Type> _val, float width, float height){
	setup(_val,width,height);
}

template<typename Type>
ofxReadOnlySlider<Type>* ofxReadOnlySlider<Type>::setup(ofParameter<Type> _val, float width, float height){
	ofxSlider<Type>::setup(_val, width, height);
	this->unregisterMouseEvents();
	this->thisFillColor =  ofColor::cyan;
	return this;
}

template<typename Type>
ofxReadOnlySlider<Type>* ofxReadOnlySlider<Type>::setup(const std::string& sliderName, Type _val, Type _min, Type _max, float width, float height){
	this->value.set(sliderName,_val,_min,_max);
	return setup(this->value,width,height);
}

template<typename Type>
void ofxReadOnlySlider<Type>::generateText(){
	if(bShowName){
		ofxSlider<Type>::generateText();	
	}else{
	std::string valStr = ofToString((int)this->value.get());
	auto inputWidth = this->getTextBoundingBox(valStr,0,0).width;
//	auto label = getTextBoundingBox(getName(), b.x + textPadding, b.y + b.height / 2 + 4);
	auto value = this->getTextBoundingBox(valStr, this->b.x + this->b.width - this->textPadding - inputWidth, this->b.y + this->b.height / 2 + 4);
	this->overlappingLabel =false;// label.getMaxX() > value.x;
	
	this->textMesh.clear();
	this->textMesh.append(this->getTextMesh(valStr, this->b.x + this->b.width - this->textPadding - this->getTextBoundingBox(valStr,0,0).width, this->b.y + this->b.height / 2 + 4));
	}
}

template<typename Type>
void ofxReadOnlySlider<Type>::showName(){
	bShowName = true;
	this->setNeedsRedraw();
	
}
template<typename Type>
void ofxReadOnlySlider<Type>::hideName(){
	bShowName = false;
	this->setNeedsRedraw();
}

template class ofxReadOnlySlider<int8_t>;
template class ofxReadOnlySlider<uint8_t>;
template class ofxReadOnlySlider<int16_t>;
template class ofxReadOnlySlider<uint16_t>;
template class ofxReadOnlySlider<int32_t>;
template class ofxReadOnlySlider<uint32_t>;
template class ofxReadOnlySlider<int64_t>;
template class ofxReadOnlySlider<uint64_t>;
template class ofxReadOnlySlider<float>;
template class ofxReadOnlySlider<double>;
