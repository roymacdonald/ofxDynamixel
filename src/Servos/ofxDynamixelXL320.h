//
//  ofxDynamixelXL320.hpp
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//

#pragma once

#include "ofxDynamixelControlTables.h"

namespace ofxDynamixel {

class XL320: public DXLBaseControlTable {
public:
	
	XL320();		
	
	
	virtual std::string getModelName(){ return  "XL320";}
	
//	Reg16 modelNumber;          // 0 , "modelNumber"                           , true
	Reg8  firmwareVersion;      // 2 , "firmwareVersion"                       , true 
	Reg8  id;                   // 3 , "id"                  , 1    , 0 , 252  , false
	Reg8  baudRate;             // 4 , "baudRate"            , 3    , 0 , 3    , false
	Reg8  returnDelayTime;      // 5 , "returnDelayTime"     , 250  , 0 , 254  , false
	Reg16 cwAngleLimit;         // 6 , "cwAngleLimit"        , 0    , 0 , 1023 , false
	Reg16 ccwAngleLimit;        // 8 , "ccwAngleLimit"       , 1023 , 0 , 1023 , false
	
	
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

}
