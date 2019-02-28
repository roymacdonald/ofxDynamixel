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
		baseDxlParameter(uint16_t a, std::string n, bool readOnly, bool eeprom, std::string g): address(a), name(n),bReadOnly(readOnly), bEeprom(eeprom),groupHierarchy(g){}
		virtual void set(uint16_t a, std::string n, bool readOnly, bool eeprom, std::string groupHierarchy){
			address = a;
			name = n;
			bReadOnly = readOnly;
			bEeprom = eeprom;
			this->groupHierarchy = groupHierarchy;
		}
		
		uint16_t address;
		std::string name;
		std::string groupHierarchy;
		bool bReadOnly = false;
		bool bEeprom = false;
		
		
		const std::string& getType(){
			return type;
		}
		uint8_t getLength() {return length; }
	
		
		virtual void setReadOnlyValue(const uint32_t & v) = 0;
		
	protected:
		uint8_t length = 0;
		std::string type;
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
			type = typeid(ValType).name();
		}
		virtual void setReadOnlyValue(const uint32_t & v) override{
			R_value = v;
		}
		void set(uint16_t a, std::string n, ValType iVal, bool readOnly, bool eeprom, std::string groupHierachy){
			baseDxlParameter::set(a, n, readOnly, eeprom,groupHierachy);
			length = sizeof(ValType);
			R_value.set(n + "_R", iVal);
		
//			std::cout << n << "   type: " << type << std::endl; 
			if(!bReadOnly){
				W_value.set(n+ "_W", iVal);
				listener = W_value.newListener(this, &dxlParameter::valChanged);
			}
		}
		 
		void set(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom, std::string groupHierachy){
			set(a, n, iVal, readOnly, eeprom,groupHierachy);
			R_value.setMin( mn);
			R_value.setMax( mx);
			if(!bReadOnly){
				W_value.setMin( mn);
				W_value.setMax( mx);
			}
			
			//			baseDxlParameter::set(a, n, readOnly, eeprom);
//			length = sizeof(ValType);
//			R_value.set(n + "_R", iVal, mn, mx);
//			if(!bReadOnly){
//				W_value.set(n+ "_W", iVal);
//				listener = W_value.newListener(this, &dxlParameter::valChanged);
//			}
//			type = typeid(*this).name();
		}
		void valChanged(ValType& v){
			dxlEventType e;
			e.data = v;
			e.address = address;
			e.length = length;
			ofNotifyEvent(changeEvent, e, this);
		}
		
		
		virtual void set(uint16_t a, std::string n, bool readOnly, bool eeprom, std::string groupHierachy){
			set(a, n, 0, 0, std::numeric_limits<ValType>::max(), readOnly, eeprom, groupHierachy);
		}
		
		dxlParameter<ValType>(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom, std::string groupHierachy):dxlParameter<ValType>(){
			set(a, n, iVal, mn, mx, readOnly, eeprom, groupHierachy);
			//			std::cout << __PRETTY_FUNCTION__ << "  " << n << " , " << iVal << " , " << mn << " , " << mx << std::endl;
		}
		dxlParameter<ValType>(uint16_t a, std::string n, bool readOnly, bool eeprom, std::string groupHierachy):dxlParameter<ValType>(){
			set(a,n,readOnly, eeprom, groupHierachy);
		}
		
		
		
		ofEvent<dxlEventType> changeEvent;
		
	protected:
		ofEventListener listener;
	private:
		
		
	};
	
	
	typedef dxlParameter<bool> RegBool;
	typedef dxlParameter<uint8_t> Reg8;
	typedef dxlParameter<uint16_t> Reg16;
	typedef dxlParameter<uint32_t> Reg32;

}
