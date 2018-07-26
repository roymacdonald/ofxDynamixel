//
//  ofxDynamixelControlTables.h
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//
#pragma once
#include <string>
#include <limits>
#include <cstdint>
#include <vector>
#include "ofParameter.h"


namespace ofxDynamixel {

	
	class baseRegStruct{
	public:
		baseRegStruct(){}
		virtual ~baseRegStruct(){}
		baseRegStruct(uint16_t a, std::string n, bool readOnly, bool eeprom): address(a), name(n),bReadOnly(readOnly), bEeprom(eeprom){}
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
		
		
	protected:
		
		
		
	};

	struct dxlEventType{
		uint32_t data;
		uint16_t address;
		uint8_t length;
		
	};
	
	
	template<typename ValType>
	class regStruct: public baseRegStruct{
	public:
		ofParameter<ValType> W_value;
		ofParameter<ValType> R_value;
		regStruct<ValType>(){}

		void set(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			baseRegStruct::set(a, n, readOnly, eeprom);
			R_value.set(n + "_R", iVal, mn, mx);
			if(!bReadOnly){
				W_value.set(n+ "_W", iVal, mn, mx);
				listener = W_value.newListener([&](ValType& v){
					dxlEventType e;
					e.data = v;
					e.address = address;
					e.length = sizeof(ValType);
					ofNotifyEvent(changeEvent, e, this);
				});
			}
			type = typeid(*this).name();
			
		}
		virtual void set(uint16_t a, std::string n, bool readOnly, bool eeprom){
			set(a, n, 0, 0, std::numeric_limits<ValType>::max(), readOnly, eeprom);
		}
		regStruct<ValType>(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			set(a, n, iVal, mn, mx, readOnly, eeprom);
//			std::cout << __PRETTY_FUNCTION__ << "  " << n << " , " << iVal << " , " << mn << " , " << mx << std::endl;
		}
		regStruct<ValType>(uint16_t a, std::string n, bool readOnly, bool eeprom){
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
	


	typedef regStruct<uint8_t> Reg8;
	typedef regStruct<uint16_t> Reg16;

	class  DXLBaseRegister{
	public:
		DXLBaseRegister();
		virtual ~DXLBaseRegister(){} 
		virtual std::string getModelName(){return "";}

		Reg16 modelNumber;          // 0 , "modelNumber"                           , true
		Reg8  firmwareVersion;      // 2 , "firmwareVersion"                       , true 
		Reg8  id;                   // 3 , "id"                  , 1    , 0 , 252  , false
		Reg8  baudRate;             // 4 , "baudRate"            , 3    , 0 , 3    , false
		Reg8  returnDelayTime;      // 5 , "returnDelayTime"     , 250  , 0 , 254  , false
		Reg16 cwAngleLimit;         // 6 , "cwAngleLimit"        , 0    , 0 , 1023 , false
		Reg16 ccwAngleLimit;        // 8 , "ccwAngleLimit"       , 1023 , 0 , 1023 , false


		//std::map<std::string, baseRegStruct *> table;
		std::vector<baseRegStruct *> table;
		
		ofEvent<dxlEventType> paramChangeEvent;
		
	protected:
		template<typename ValType>
		void add(regStruct<ValType>& s, uint16_t a, std::string n, bool readOnly, bool eeprom){

			s.set(a,n, readOnly, eeprom);
			
			table.push_back(&s);

		}

		template<typename ValType>
		void add(regStruct<ValType>& s, uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx, bool readOnly, bool eeprom){
			s.set(a, n, iVal, mn, mx, readOnly, eeprom);
			listeners.push(s.changeEvent.newListener([&](dxlEventType& e){
				ofNotifyEvent(paramChangeEvent, e, this);
			}));
			
			table.push_back(&s);
		}
		ofEventListeners listeners;
	};
	
	class XL320: public DXLBaseRegister {
	public:
		
		XL320();		
		

		virtual std::string getModelName(){ return  "XL320";}

		Reg8 controlMode;           //   11 , "controlMode"       , 2    , 1  , 2    , false,  1 bytes,  Control Mode
		Reg8 temperatureLimit;      //   12 , "temperatureLimit"  , 65   , 0  , 150  , false,  1 bytes,  Maximum Internal Temperature Limit
		Reg8 minVoltageLimit;       //   13 , "minVoltageLimit"   , 60   , 50 , 250  , false,  1 bytes,  Minimum Input Voltage Limit
		Reg8 maxVoltageLimit;       //   14 , "maxVoltageLimit"   , 90   , 50 , 250  , false,  1 bytes,  Maximum Input Voltage Limit
		Reg16 maxTorque;            //   15 , "maxTorque"         , 1023 , 0  , 1023 , false,  2 bytes,  Maximun Torque
		Reg8 statusReturnLevel;     //   17 , "statusReturnLevel" , 2    , 0  , 2    , false,  1 bytes,  Select Types of Status Return
		Reg8 shutdown;              //   18 , "shutdown"          , 3    , 0  , 7    , false,  1 bytes,  Shutdown Error Information
		Reg8 torqueEnabled;         //   24 , "torqueEnable"      , 0    , 0  , 1    , false,  1 bytes,  Motor Torque On/Off
		Reg8 led;                   //   25 , "led"               , 0    , 0  , 7    , false,  1 bytes,  Status LED On/Off
		Reg8 dGain;                 //   27 , "dGain"             , 0    , 0  , 254  , false,  1 bytes,  Derivative Gain
		Reg8 iGain;                 //   28 , "iGain"             , 0    , 0  , 254  , false,  1 bytes,  Integral Gain
		Reg8 pGain;                 //   29 , "pGain"             , 32   , 0  , 254  , false,  1 bytes,  Proportional Gain
		Reg16 goalPosition;         //   30 , "goalPosition"      , 0    , 0  , 1023 , false,  2 bytes,  Desired Position
		Reg16 goalSpeed;            //   32 , "goalSpeed"         , 0    , 0  , 2047 , false,  2 bytes,  Moving Speed(Moving Velocity
		Reg16 torqueLimit;          //   35 , "torqueLimit"       , 0    , 0  , 1023 , false,  2 bytes,  Torque Limit(Goal Torque
		Reg16 punch;                //   51 , "punch"             , 32   , 0  , 1023 , false,  2 bytes,  Minimum Current Threshold
		Reg16 presentPosition;      //   37 , "presentPosition"   , 0    , 0  , 1023 , true),  2 bytes,  Present Position 
		Reg16 presentSpeed;         //   39 , "presentSpeed"      , 0    , 0  , 2047 , true),  2 bytes,  Present Speed
		Reg16 presentLoad;          //   41 , "presentLoad"       , 0    , 0  , 2047 , true),  2 bytes,  Present Load
		Reg8 presentVoltage;        //   45 , "presentVoltage"                      , true);,  1 bytes,  Present Voltage       
		Reg8 presentTemperature;    //   46 , "presentTemperature"                  , true);,  1 bytes,  Present Temperature
		Reg8 registered;            //   47 , "registered"                          , true);,  1 bytes,  If Instruction is registered
		Reg8 moving;                //   49 , "moving"           , 0    , 0  ,    1 , true);,  1 bytes,  Movement Status       
		Reg8 hardwareErrorStatus;   //   50 , "hardwareErrorStatus"                 , true);,  1 bytes,  Hardware Error Status
			
	};
	
	
	class AX12: public DXLBaseRegister {
	public:
		AX12();
		std::string getModelName(){return "AX12";}
		Reg8 temperatureLimit;      //    11  , "temperatureLimit");}    // 1 bytes.  Maximum Internal Temperature Limit | RW | 70
		Reg8 minVoltageLimit;       //    12  , "minVoltageLimit");}     // 1 bytes.  Minimum Input Voltage Limit         | RW | 60
		Reg8 maxVoltageLimit;       //    13  , "maxVoltageLimit");}     // 1 bytes.  Maximum Input Voltage Limit         | RW | 140
		Reg16 maxTorque;            //    14  , "maxTorque");}            // 2 bytes.  Maximun Torque                    | RW | 1023
		Reg8 statusReturnLevel;     //    16  , "statusReturnLevel");}   // 1 bytes.  Select Types of Status Return       | RW | 2
		Reg8 alarmLed;              //    17  , "alarmLed");}            // 1 bytes.  LED for Alarm                      | RW | 36
		Reg8 shutdown;              //    18  , "shutdown");}            // 1 bytes.  Shutdown Error Information        | RW | 36
		Reg8 torqueEnabled;         //    24  , "torqueEnable");}        // 1 bytes.  Motor Torque On/Off                | RW | 0
		Reg8 led;                   //    25  , "led");}                 // 1 bytes.  Status LED On/Off                 | RW | 0
		Reg8 cwComplianceMargin;    //    26  , "cwComplianceMargin");}  // 1 bytes.  CW Compliance Margin                | RW | 1
		Reg8 ccwComplianceMargin;   //    27  , "ccwComplianceMargin");} // 1 bytes.  CCW Compliance Margin               | RW | 1
		Reg8 cwComplianceSlope;     //    28  , "cwComplianceSlope");}   // 1 bytes.  CW Compliance Slope                 | RW | 32
		Reg8 ccwComplianceSlope;    //    29  , "ccwComplianceSlope");}  // 1 bytes.  CCW Compliance Slope                | RW | 32
		Reg16 goalPosition;         //    30  , "goalPosition");}         // 2 bytes.  Target Position                   | RW | -
		Reg16 goalSpeed;            //    32  , "goalSpeed");}            // 2 bytes.  Moving Speed                      | RW | -
		Reg16 torqueLimit;          //    34  , "torqueLimit");}          // 2 bytes.  Torque Limit(Goal Torque)         | RW | ADD 1415
		Reg16 presentPosition;      //    36  , "presentPosition");}      // 2 bytes.  Present Position                  | R  | -
		Reg16 presentSpeed;         //    38  , "presentSpeed");}         // 2 bytes.  Present Speed                     | R  | -
		Reg16 presentLoad;          //    40  , "presentLoad");}          // 2 bytes.  Present Load                      | R  | -
		Reg8 presentVoltage;        //    42  , "presentVoltage");}      // 1 bytes.  Present Voltage                    | R  | -
		Reg8 presentTemperature;    //    43  , "presentTemperature");}  // 1 bytes.  Present Temperature                | R  | -
		Reg8 registered;            //    44  , "registered");}          // 1 bytes.  If Instruction is registered      | R  | 0
		Reg8 moving;                //    46  , "moving");}              // 1 bytes.  Movement Status                   | R  | 0
		Reg8 lock;                  //    47  , "lock");}                // 1 bytes.  Locking EEPROM                    | RW | 0
		Reg16 punch;                //    48  , "punch");}                // 2 bytes.  Minimum Current Threshold        | RW | 32
		

	};
}
