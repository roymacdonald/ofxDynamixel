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

namespace ofxDynamixel {
	template<typename ValType>
	class regStruct{
	public:
		uint16_t address;
		std::string name;
		ValType minValue, maxValue, initValue;
		regStruct<ValType>(){}
		regStruct<ValType>(uint16_t a, std::string n, ValType iVal, ValType mn, ValType mx): address(a), name(n), minValue(mn), maxValue(mx), initValue(iVal){}
		regStruct<ValType>(uint16_t a, std::string n): address(a), name(n), initValue(0), minValue(0), maxValue(std::numeric_limits<ValType>::max()){}
	};
//	template class Reg8;
//	template class regStruct<uint16_t>;
	typedef regStruct<uint8_t> Reg8;
	typedef regStruct<uint16_t> Reg16;

	class  DXLBaseRegister{
	public:
		inline static Reg16 modelNumber(){     return Reg16(0 , "modelNumber");}
		inline static Reg8  firmwareVersion(){ return Reg8( 2 , "firmwareVersion" );}
		inline static Reg8  id(){              return Reg8( 3 , "id"                  , 1    , 0 , 252 );}
		inline static Reg8  baudRate(){        return Reg8( 4 , "baudRate"            , 3    , 0 , 3 );}
		inline static Reg8  returnDelayTime(){ return Reg8( 5 , "returnDelayTime"     , 250  , 0 , 254  );}
		inline static Reg16 cwAngleLimit(){    return Reg16(6 , "cwAngleLimit"        , 0    , 0 , 1023 );}
		inline static Reg16 ccwAngleLimit(){   return Reg16(8 , "ccwAngleLimit"       , 1023 , 0 , 1023 );}
		
	};
	
	class XL320: public DXLBaseRegister {
	public:
		inline static std::string getModelName(){ return  "XL320";}
		inline static Reg8 controlMode(){         return Reg8 (11  , "controlMode"       , 2    , 1  , 2);}    // 1 bytes. Control Mode                        RW 2    , 1  , 2
		inline static Reg8 temperatureLimit(){    return Reg8 (12  , "temperatureLimit"  , 65   , 0  , 150);}  // 1 bytes. Maximum Internal Temperature Limit  RW 65   , 0  , 150
		inline static Reg8 minVoltageLimit(){     return Reg8 (13  , "minVoltageLimit"   , 60   , 50 , 250);}  // 1 bytes. Minimum Input Voltage Limit         RW 60   , 50 , 250
		inline static Reg8 maxVoltageLimit(){     return Reg8 (14  , "maxVoltageLimit"   , 90   , 50 , 250);}  // 1 bytes. Maximum Input Voltage Limit         RW 90   , 50 , 250
		inline static Reg16 maxTorque(){          return Reg16 (15 , "maxTorque"         , 1023 , 0  , 1023);} // 2 bytes. Maximun Torque                      RW 1023 , 0  , 1023
		inline static Reg8 statusReturnLevel(){   return Reg8 (17  , "statusReturnLevel" , 2    , 0  , 2);}    // 1 bytes. Select Types of Status Return       RW 2    , 0  , 2
		inline static Reg8 shutdown(){            return Reg8 (18  , "shutdown"          , 3    , 0  , 7);}    // 1 bytes. Shutdown Error Information          RW 3    , 0  , 7
		inline static Reg8 torqueEnabled(){        return Reg8 (24  , "torqueEnable"      , 0    , 0  , 1);}    // 1 bytes. Motor Torque On/Off                 RW 0    , 0  , 1
		inline static Reg8 led(){                 return Reg8 (25  , "led"               , 0    , 0  , 7);}    // 1 bytes. Status LED On/Off                   RW 0    , 0  , 7
		inline static Reg8 dGain(){               return Reg8 (27  , "dGain"             , 0    , 0  , 254);}  // 1 bytes. Derivative Gain                     RW 0    , 0  , 254
		inline static Reg8 iGain(){               return Reg8 (28  , "iGain"             , 0    , 0  , 254);}  // 1 bytes. Integral Gain                       RW 0    , 0  , 254
		inline static Reg8 pGain(){               return Reg8 (29  , "pGain"             , 32   , 0  , 254);}  // 1 bytes. Proportional Gain                   RW 32   , 0  , 254
		inline static Reg16 goalPosition(){       return Reg16 (30 , "goalPosition"      , 0    , 0  , 1023);} // 2 bytes. Desired Position                    RW -    , 0  , 1023
		inline static Reg16 goalSpeed(){        return Reg16 (32 , "goalSpeed"       , 0    , 0  , 2047);} // 2 bytes. Moving Speed(Moving Velocity)       RW -    , 0  , 2047
		inline static Reg16 torqueLimit(){        return Reg16 (35 , "torqueLimit"       , 0    , 0  , 1023);} // 2 bytes. Torque Limit(Goal Torque)           RW -    , 0  , 1023
		inline static Reg16 punch(){              return Reg16 (51 , "punch"             , 32   , 0  , 1023);} // 2 bytes. Minimum Current Threshold           RW 32   , 0  , 1023
		inline static Reg16 presentPosition(){    return Reg16 (37 , "presentPosition"   , 0    , 0  , 1023);} // 2 bytes. Present Position                    R
		inline static Reg16 presentSpeed(){       return Reg16 (39 , "presentSpeed"      , 0    , 0  , 2047);} // 2 bytes. Present Speed                       R
		inline static Reg16 presentLoad(){        return Reg16 (41 , "presentLoad"       , 0    , 0  , 2047);} // 2 bytes. Present Load                        R
		inline static Reg8 presentVoltage(){      return Reg8 (45  , "presentVoltage");}                       // 1 bytes. Present Voltage                     R
		inline static Reg8 presentTemperature(){  return Reg8 (46  , "presentTemperature");}                   // 1 bytes. Present Temperature                 R
		inline static Reg8 registered(){          return Reg8 (47  , "registered");}                           // 1 bytes. If Instruction is registered        R
		inline static Reg8 moving(){              return Reg8 (49  , "moving" , 0 , 0 , 1);}                   // 1 bytes. Movement Status                     R
		inline static Reg8 hardwareErrorStatus(){ return Reg8 (50  , "hardwareErrorStatus");}                  // 1 bytes. Hardware Error Status               R
		
		//not maent to be used
		inline static Reg8 cwComplianceMargin(){  return Reg8();}
		inline static Reg8 ccwComplianceMargin(){ return Reg8();}
		inline static Reg8 cwComplianceSlope(){   return Reg8();}
		inline static Reg8 ccwComplianceSlope(){  return Reg8();}
		inline static Reg8 lock(){return Reg8();}
		
		
	};
	
	
	class AX12: public DXLBaseRegister {
	public:
		inline static std::string getModelName(){return "AX12";}
		inline static Reg8 temperatureLimit(){    return Reg8 (11  , "temperatureLimit");}     // 1 bytes.  Maximum Internal Temperature Limit | RW | 70
		inline static Reg8 minVoltageLimit(){     return Reg8 (12  , "minVoltageLimit");}     // 1 bytes.  Minimum Input Voltage Limit         | RW | 60
		inline static Reg8 maxVoltageLimit(){     return Reg8 (13  , "maxVoltageLimit");}     // 1 bytes.  Maximum Input Voltage Limit         | RW | 140
		inline static Reg16 maxTorque(){          return Reg16 (14 , "maxTorque");}            // 2 bytes.  Maximun Torque                    | RW | 1023
		inline static Reg8 statusReturnLevel(){   return Reg8 (16  , "statusReturnLevel");}   // 1 bytes.  Select Types of Status Return       | RW | 2
		inline static Reg8 alarmLed(){            return Reg8 (17  , "alarmLed");}             // 1 bytes.  LED for Alarm                      | RW | 36
		inline static Reg8 shutdown(){            return Reg8 (18  , "shutdown");}              // 1 bytes.  Shutdown Error Information        | RW | 36
		inline static Reg8 torqueEnabled(){        return Reg8 (24  , "torqueEnable");}         // 1 bytes.  Motor Torque On/Off                | RW | 0
		inline static Reg8 led(){                 return Reg8 (25  , "led");}                   // 1 bytes.  Status LED On/Off                 | RW | 0
		inline static Reg8 cwComplianceMargin(){  return Reg8 (26  , "cwComplianceMargin");}  // 1 bytes.  CW Compliance Margin                | RW | 1
		inline static Reg8 ccwComplianceMargin(){ return Reg8 (27  , "ccwComplianceMargin");} // 1 bytes.  CCW Compliance Margin               | RW | 1
		inline static Reg8 cwComplianceSlope(){   return Reg8 (28  , "cwComplianceSlope");}   // 1 bytes.  CW Compliance Slope                 | RW | 32
		inline static Reg8 ccwComplianceSlope(){  return Reg8 (29  , "ccwComplianceSlope");}  // 1 bytes.  CCW Compliance Slope                | RW | 32
		inline static Reg16 goalPosition(){       return Reg16 (30 , "goalPosition");}         // 2 bytes.  Target Position                   | RW | -
		inline static Reg16 goalSpeed(){        return Reg16 (32 , "goalSpeed");}          // 2 bytes.  Moving Speed                      | RW | -
		inline static Reg16 torqueLimit(){        return Reg16 (34 , "torqueLimit");}          // 2 bytes.  Torque Limit(Goal Torque)         | RW | ADD 1415
		inline static Reg16 presentPosition(){    return Reg16 (36 , "presentPosition");}      // 2 bytes.  Present Position                  | R  | -
		inline static Reg16 presentSpeed(){       return Reg16 (38 , "presentSpeed");}         // 2 bytes.  Present Speed                     | R  | -
		inline static Reg16 presentLoad(){        return Reg16 (40 , "presentLoad");}          // 2 bytes.  Present Load                      | R  | -
		inline static Reg8 presentVoltage(){      return Reg8 (42  , "presentVoltage");}       // 1 bytes.  Present Voltage                    | R  | -
		inline static Reg8 presentTemperature(){  return Reg8 (43  , "presentTemperature");}   // 1 bytes.  Present Temperature                | R  | -
		inline static Reg8 registered(){          return Reg8 (44  , "registered");}            // 1 bytes.  If Instruction is registered      | R  | 0
		inline static Reg8 moving(){              return Reg8 (46  , "moving");}                // 1 bytes.  Movement Status                   | R  | 0
		inline static Reg8 lock(){                return Reg8 (47  , "lock");}                  // 1 bytes.  Locking EEPROM                    | RW | 0
		inline static Reg16 punch(){              return Reg16 (48 , "punch");}                 // 2 bytes.  Minimum Current Threshold        | RW | 32
		
		//not meant to be used
		inline static Reg8 controlMode(){return Reg8();}
		inline static Reg8 dGain(){return Reg8();}
		inline static Reg8 iGain(){return Reg8();}
		inline static Reg8 pGain(){return Reg8();}
		inline static Reg8 hardwareErrorStatus(){return Reg8();}
	};
}
