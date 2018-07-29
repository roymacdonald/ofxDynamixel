//
//  ofxDynamixelControlTables.h
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//
#pragma once
#include <vector>
#include "ofxDynamixelParameter.h"

namespace ofxDynamixel {
	class  DXLBaseControlTable{
	public:
		DXLBaseControlTable();
		virtual ~DXLBaseControlTable(){} 
		virtual std::string getModelName(){return "";}

		Reg16 modelNumber;          // 0 , "modelNumber"                           , true
//		Reg8  firmwareVersion;      // 2 , "firmwareVersion"                       , true 
//		Reg8  id;                   // 3 , "id"                  , 1    , 0 , 252  , false
//		Reg8  baudRate;             // 4 , "baudRate"            , 3    , 0 , 3    , false
//		Reg8  returnDelayTime;      // 5 , "returnDelayTime"     , 250  , 0 , 254  , false
//		Reg16 cwAngleLimit;         // 6 , "cwAngleLimit"        , 0    , 0 , 1023 , false
//		Reg16 ccwAngleLimit;        // 8 , "ccwAngleLimit"       , 1023 , 0 , 1023 , false


		//std::map<std::string, baseDxlParameter *> table;
		std::vector<baseDxlParameter *> table;
		
		ofEvent<dxlEventType> paramChangeEvent;
		
	protected:
		template<typename ValType>
		void add(dxlParameter<ValType>& s, uint16_t a, std::string n, bool readOnly, bool eeprom){

			s.set(a,n, readOnly, eeprom);
			
			table.push_back(&s);

		}

		
		void addBool(dxlParameter<bool>& s, uint16_t a, std::string n, bool iVal, bool readOnly, bool eeprom){
			s.set(a, n, iVal, readOnly, eeprom);
			listeners.push(s.changeEvent.newListener([&](dxlEventType& e){
				ofNotifyEvent(paramChangeEvent, e, this);
			}));
			
			table.push_back(&s);
			std::cout << "added bool to table" << std::endl;
		}
		
		
		template<typename ValType>
		void add(dxlParameter<ValType>& s, uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			s.set(a, n, iVal, mn, mx, readOnly, eeprom);
			listeners.push(s.changeEvent.newListener([&](dxlEventType& e){
				ofNotifyEvent(paramChangeEvent, e, this);
			}));
			
			table.push_back(&s);
		}
		ofEventListeners listeners;
	};
	
		
	
	
}
