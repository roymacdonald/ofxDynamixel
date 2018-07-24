//
//  ofxGuiRWSlider.hpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#pragma once
//#include "ofxGui.h"
#include "ofxGuiGroupMinimal.h"
#include "ofxDynamixelRWParameter.h"

template<class T>
class ofxGuiRWSlider_ : public ofxGuiGroupMinimal {
public:
	ofxGuiRWSlider_(){
//		sliderChanging = false;
	};
	ofxGuiRWSlider_(ofxDynamixel::RWParameter<T> value, float width = defaultWidth, float height = defaultHeight);
	
	ofxGuiRWSlider_ * setup(ofxDynamixel::RWParameter<T> value, float width = defaultWidth, float height = defaultHeight);
	
//	void add(ofxDynamixel::RWParameter <uint8_t> & parameter);
//	void add(ofxDynamixel::RWParameter <uint16_t> & parameter);
//	
	
	ofxDynamixel::RWParameter<T>& getRWParameter();
//	ofAbstractParameter & getParameter();
	
//	T operator=(const T & v);
//	operator const T & ();
//	const T * operator->();
protected:
//	void changeSlider(const void * parameter, float & value);
//	void changeValue(T & value);
	ofxDynamixel::RWParameter<T> value;
//	bool sliderChanging;
};

typedef ofxGuiRWSlider_<uint8_t> ofxSliderRW_U8;
typedef ofxGuiRWSlider_<uint16_t> ofxSliderRW_U16;
