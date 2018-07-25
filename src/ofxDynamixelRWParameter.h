//
//  ofxDynamixelRWParameter.hpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//
#pragma once
#include "ofParameter.h"
#include "ofxDynamixelControlTables.h"
namespace ofxDynamixel {
	template<typename ParameterType>
	class RWParameter{
		public:
		RWParameter(){}
		RWParameter(const regStruct<ParameterType>& reg){
			set(reg);
		}
		RWParameter(const std::string& name, const ParameterType & v, const uint16_t & command ){
			set(name, v, command);	
		}
		RWParameter(const std::string& name, const ParameterType & v, const uint16_t & command, const ParameterType & min, const ParameterType & max){
			set(name, v, command, min, max);
		}			
		
		RWParameter<ParameterType>& set(const regStruct<ParameterType>& reg){
			set(reg.name, reg.initValue, reg.address, reg.minValue, reg.maxValue );
		}
		RWParameter<ParameterType>& set(const std::string& name, const ParameterType & v, const uint16_t & command ){
			this->name = name;
			readOnlyParam.set(name+"_R", v);
			writeParam.set(name+"_W", v);
			dxl_command = command;
			return *this;
		}
		
		RWParameter<ParameterType>& set(const std::string& name, const ParameterType & v, const uint16_t & command, const ParameterType & min, const ParameterType & max){
			set(name, v, command);
			readOnlyParam.setMin(min);
			readOnlyParam.setMax(max);
			writeParam.setMin(min);
			writeParam.setMax(max);
			return *this;
		}
	
		
		
		ofParameter<ParameterType> readOnlyParam;
		ofParameter<ParameterType> writeParam;
		
		uint16_t dxl_command;
		const std::string& getName(){return name;}
		void setName(const std::string& n ){name = n;}
	protected:
		std::string name;
	};	
}
