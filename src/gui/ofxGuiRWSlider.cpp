//
//  ofxGuiRWSlider.cpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofxGuiRWSlider.h"

using namespace std;

template<class T>
ofxGuiRWSlider_<T>::ofxGuiRWSlider_(ofxDynamixel::RWParameter<T> value, float width, float height){
//	sliderChanging = false;
	setup(value, width, height);
}

template<class T>
ofxGuiRWSlider_<T> * ofxGuiRWSlider_<T>::setup(ofxDynamixel::RWParameter<T> value, float width, float height){
	ofxGuiGroup::setup(value.getName(), "", 0, 0);

	parameters.clear();
	
	ofxGuiGroup::add(value.readOnlyParam);
	ofxGuiGroup::add(value.writeParam);
	
	this->value.readOnlyParam.makeReferenceTo(value.readOnlyParam);
	this->value.writeParam.makeReferenceTo(value.writeParam);
	this->value.setName(value.getName());
	this->value.dxl_command = value.dxl_command; 
	
//	value.readOnlyParam.addListener(this, & ofxGuiRWSlider_::changeSlider);
//	value.writeParam.addListener(this, & ofxGuiRWSlider_::changeSlider);
	
//	sliderChanging = false;
	return this;
	
}
template<class T>
ofxDynamixel::RWParameter<T>& ofxGuiRWSlider_<T>::getRWParameter(){
	return value;
}

//template<class T>
//void ofxGuiRWSlider_<T>::changeSlider(const void * parameter, float & _value){
//	sliderChanging = true;
//	ofParameter<T> & param = *(ofParameter<T>*)parameter;
////	int i = parameters.getPosition(param.getName());
////	T data = value;
////	data[i] = _value;
////	value = data;
//	sliderChanging = false;
//}

//template<class T>
//void ofxGuiRWSlider_<T>::changeValue(T & value){
//	if (sliderChanging){
//		return;
//	}
//	for (size_t i = 0; i < dim(); i++){
//		parameters[i].template cast<float>() = value[i];
//	}
//}


//template<class T>
//ofAbstractParameter & ofxGuiRWSlider_<T>::getParameter(){
//	return value;
//}

//template<class T>
//T ofxGuiRWSlider_<T>::operator=(const T & v){
//	value = v;
//	return value;
//}
//
//template<class T>
//ofxGuiRWSlider_<T>::operator const T & (){
//	return value;
//}
//
//template<class T>
//const T * ofxGuiRWSlider_<T>::operator->(){
//	return &value;
//}

template class ofxGuiRWSlider_<uint8_t>;
template class ofxGuiRWSlider_<uint16_t>;
