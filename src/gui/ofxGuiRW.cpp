//
//  ofxGuiRWSlider.cpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofxGuiRW.h"
#include "ofxReadOnlySlider.h"

using namespace std;

template<class T>
ofxGuiRW_<T>::ofxGuiRW_(ofxDynamixel::RWParameter<T> value, float width, float height){
//	sliderChanging = false;
	setup(value, width, height);
}

template<class T>
ofxGuiRW_<T> * ofxGuiRW_<T>::setup(ofxDynamixel::RWParameter<T> value, float width, float height){
	ofxGuiGroupMinimal::setup(value.getName(), "", 0, 0);

	parameters.clear();
	
	ofxGuiGroupMinimal::add(value.writeParam);
	if(std::is_arithmetic<T>::value){
		ofxGuiGroupMinimal::add(new ofxReadOnlySlider<T>(value.readOnlyParam));
	}else{
	
	}
	
	this->value.readOnlyParam.makeReferenceTo(value.readOnlyParam);
	this->value.writeParam.makeReferenceTo(value.writeParam);
	this->value.setName(value.getName());
	this->value.dxl_command = value.dxl_command; 
	
//	value.readOnlyParam.addListener(this, & ofxGuiRW_::changeSlider);
//	value.writeParam.addListener(this, & ofxGuiRW_::changeSlider);
	
//	sliderChanging = false;
	return this;
	
}
template<class T>
ofxDynamixel::RWParameter<T>& ofxGuiRW_<T>::getRWParameter(){
	return value;
}

//template<class T>
//void ofxGuiRW_<T>::changeSlider(const void * parameter, float & _value){
//	sliderChanging = true;
//	ofParameter<T> & param = *(ofParameter<T>*)parameter;
////	int i = parameters.getPosition(param.getName());
////	T data = value;
////	data[i] = _value;
////	value = data;
//	sliderChanging = false;
//}

//template<class T>
//void ofxGuiRW_<T>::changeValue(T & value){
//	if (sliderChanging){
//		return;
//	}
//	for (size_t i = 0; i < dim(); i++){
//		parameters[i].template cast<float>() = value[i];
//	}
//}


//template<class T>
//ofAbstractParameter & ofxGuiRW_<T>::getParameter(){
//	return value;
//}

//template<class T>
//T ofxGuiRW_<T>::operator=(const T & v){
//	value = v;
//	return value;
//}
//
//template<class T>
//ofxGuiRW_<T>::operator const T & (){
//	return value;
//}
//
//template<class T>
//const T * ofxGuiRW_<T>::operator->(){
//	return &value;
//}

template class ofxGuiRW_<uint8_t>;
template class ofxGuiRW_<uint16_t>;
template class ofxGuiRW_<bool>;
