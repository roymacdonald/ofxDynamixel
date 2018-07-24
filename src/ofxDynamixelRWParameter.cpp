//
//  ofxDynamixelRWParameter.cpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofxDynamixelRWParameter.h"

namespace ofxDynamixel {
	template<typename PType>
	RWParameter<PType>::RWParameter(const std::string& name, const PType & v, const uint16_t & command ){
		set(name, v, command);
		
	}
	template<typename PType>
	RWParameter<PType>::RWParameter(const std::string& name, const PType & v, const uint16_t & command, const PType & min, const PType & max){
		set(name, v, command, min, max);
	}	
	template<typename PType>	
	RWParameter<PType>& RWParameter<PType>::set(const std::string& name, const PType & v, const uint16_t & command ){
		this->name = name;
		readOnlyParam.set(name+"_R", v);
		writeParam.set(name+"_W", v);
		dxl_command = command;
		return *this;
	}
	template<typename PType>
	RWParameter<PType>& RWParameter<PType>::set(const std::string& name, const PType & v, const uint16_t & command, const PType & min, const PType & max){
		set(name, v, command);
		readOnlyParam.setMin(min);
		readOnlyParam.setMax(max);
		writeParam.setMin(min);
		writeParam.setMax(max);
		return *this;
	}
	
}
