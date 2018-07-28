//
//  ofxDynamixelAX12+.hpp
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//
#pragma once

#include "ofxDynamixelControlTables.h"

namespace ofxDynamixel {

	class AX12: public DXLBaseControlTable {
	public:
		AX12();
		std::string getModelName(){return "AX12";}
		
		Reg8  firmwareVersion;      // 2 , "firmwareVersion"                       , true 
		Reg8  id;                   // 3 , "id"                  , 1    , 0 , 252  , false
		Reg8  baudRate;             // 4 , "baudRate"            , 3    , 0 , 3    , false
		Reg8  returnDelayTime;      // 5 , "returnDelayTime"     , 250  , 0 , 254  , false
		Reg16 cwAngleLimit;         // 6 , "cwAngleLimit"        , 0    , 0 , 1023 , false
		Reg16 ccwAngleLimit;        // 8 , "ccwAngleLimit"       , 1023 , 0 , 1023 , false
		
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
