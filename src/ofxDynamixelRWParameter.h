//
//  ofxDynamixelRWParameter.hpp
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//

#include "ofParameter.h"
namespace ofxDynamixel {
	template<typename ParameterType>
	class RWParameter{
		public:
		RWParameter(){}
		RWParameter(const std::string& name, const ParameterType & v, const uint16_t & command );
		RWParameter(const std::string& name, const ParameterType & v, const uint16_t & command, const ParameterType & min, const ParameterType & max);		
		RWParameter<ParameterType>& set(const std::string& name, const ParameterType & v, const uint16_t & command );
		RWParameter<ParameterType>& set(const std::string& name, const ParameterType & v, const uint16_t & command, const ParameterType & min, const ParameterType & max);
		
		ofParameter<ParameterType> readOnlyParam;
		ofParameter<ParameterType> writeParam;
		
		uint16_t dxl_command;
		const std::string& getName(){return name;}
		void setName(const std::string& n ){name = n;}
	protected:
		std::string name;
	};	
}
