//
//  ofxDynamixelParameter.h
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//

#pragma once

#include <string>
#include <limits>
#include <cstdint>
#include "ofParameter.h"


namespace ofxDynamixel {
	
	
	class baseDxlParameter{
	public:
		baseDxlParameter(){}
		virtual ~baseDxlParameter(){}
		baseDxlParameter(uint16_t a, std::string n, bool readOnly, bool eeprom): address(a), name(n),bReadOnly(readOnly), bEeprom(eeprom){}
		virtual void set(uint16_t a, std::string n, bool readOnly, bool eeprom){
			address = a;
			name = n;
			bReadOnly = readOnly;
			bEeprom = eeprom;
		}
		
		uint16_t address;
		std::string name;
		bool bReadOnly = false;
		bool bEeprom = false;
		uint8_t length = 0;
		
	protected:
		
		
		
	};
	
	struct dxlEventType{
		uint32_t data;
		uint16_t address;
		uint8_t length;
		
	};
	
	
	template<typename ValType>
	class dxlParameter: public baseDxlParameter{
	public:
		ofParameter<ValType> W_value;
		ofParameter<ValType> R_value;
		dxlParameter<ValType>(){
			length = sizeof(ValType);
		}
		
		void set(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			baseDxlParameter::set(a, n, readOnly, eeprom);
			length = sizeof(ValType);
			R_value.set(n + "_R", iVal, mn, mx);
			if(!bReadOnly){
				W_value.set(n+ "_W", iVal, mn, mx);
				listener = W_value.newListener([&](ValType& v){
					dxlEventType e;
					e.data = v;
					e.address = address;
					e.length = length;
					ofNotifyEvent(changeEvent, e, this);
				});
			}
			type = typeid(*this).name();
			
		}
		virtual void set(uint16_t a, std::string n, bool readOnly, bool eeprom){
			set(a, n, 0, 0, std::numeric_limits<ValType>::max(), readOnly, eeprom);
		}
		dxlParameter<ValType>(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			set(a, n, iVal, mn, mx, readOnly, eeprom);
			//			std::cout << __PRETTY_FUNCTION__ << "  " << n << " , " << iVal << " , " << mn << " , " << mx << std::endl;
		}
		dxlParameter<ValType>(uint16_t a, std::string n, bool readOnly, bool eeprom){
			set(a,n,readOnly, eeprom);
		}
		
		const std::string& getType(){
			return type;
		}
		
		ofEvent<dxlEventType> changeEvent;
		
	protected:
		ofEventListener listener;
	private:
		std::string type;
		
	};
	
	
	
	typedef dxlParameter<uint8_t> Reg8;
	typedef dxlParameter<uint16_t> Reg16;
	typedef dxlParameter<uint32_t> Reg32;

}
