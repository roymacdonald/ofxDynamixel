//
//  ofxDynamixelAX12+.cpp
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//

#include "ofxDynamixelAX12+.h"


ofxDynamixel::AX12::AX12(){
	
	add<uint8_t >(firmwareVersion     ,  2 , "firmwareVersion"                        , true  , true);
	add<uint8_t >(id                  ,  3 , "id"                  , 1    , 0 , 252   , false , true);
	add<uint8_t >(baudRate            ,  4 , "baudRate"            , 3    , 0 ,    3  , false , true);
	add<uint8_t >(returnDelayTime     ,  5 , "returnDelayTime"     , 250  , 0 , 254   , false , true);
	add<uint16_t>(cwAngleLimit        ,  6 , "cwAngleLimit"        , 0    , 0 , 1023  , false , true);
	add<uint16_t>(ccwAngleLimit       ,  8 , "ccwAngleLimit"       , 1023 , 0 , 1023  , false , true);

	
	add<uint8_t> (temperatureLimit  , 11 , "temperatureLimit"  , 0 , 0 , 70   , false, true); // 1 bytes.  Maximum Internal Temperature Limit | RW | 70
	add<uint8_t> (minVoltageLimit   , 12 , "minVoltageLimit"   , 0 , 0 , 60   , false, true); // 1 bytes.  Minimum Input Voltage Limit        | RW | 60
	add<uint8_t> (maxVoltageLimit   , 13 , "maxVoltageLimit"   , 0 , 0 , 140  , false, true); // 1 bytes.  Maximum Input Voltage Limit        | RW | 140
	add<uint16_t> (maxTorque        , 14 , "maxTorque"         , 0 , 0 , 1023 , false, true); // 2 bytes.  Maximun Torque                     | RW | 1023
	add<uint8_t> (statusReturnLevel , 16 , "statusReturnLevel" , 0 , 0 , 2    , false, true); // 1 bytes.  Select Types of Status Return      | RW | 2
	add<uint8_t> (alarmLed          , 17 , "alarmLed"          , 0 , 0 , 36   , false, true); // 1 bytes.  LED for Alarm                      | RW | 36
	add<uint8_t> (shutdown          , 18 , "shutdown"          , 0 , 0 , 36   , false, true); // 1 bytes.  Shutdown Error Information         | RW | 36
	
	add<uint8_t> (torqueEnabled       , 24 , "torqueEnable"        , 0 , 0 , 0  , false, false); // 1 bytes.  Motor Torque On/Off                | RW | 0
	add<uint8_t> (led                 , 25 , "led"                 , 0 , 0 , 0  , false, false); // 1 bytes.  Status LED On/Off                  | RW | 0
	add<uint8_t> (cwComplianceMargin  , 26 , "cwComplianceMargin"  , 0 , 0 , 1  , false, false); // 1 bytes.  CW Compliance Margin               | RW | 1
	add<uint8_t> (ccwComplianceMargin , 27 , "ccwComplianceMargin" , 0 , 0 , 1  , false, false); // 1 bytes.  CCW Compliance Margin              | RW | 1
	add<uint8_t> (cwComplianceSlope   , 28 , "cwComplianceSlope"   , 0 , 0 , 32 , false, false); // 1 bytes.  CW Compliance Slope                | RW | 32
	add<uint8_t> (ccwComplianceSlope  , 29 , "ccwComplianceSlope"  , 0 , 0 , 32 , false, false); // 1 bytes.  CCW Compliance Slope               | RW | 32
	add<uint16_t> (goalPosition       , 30 , "goalPosition"        , false, false); // 2 bytes.  Target Position                    | RW | -
	add<uint16_t> (goalSpeed          , 32 , "goalSpeed"           , false, false); // 2 bytes.  Moving Speed                       | RW | -
	add<uint16_t> (torqueLimit        , 34 , "torqueLimit"         , false, false); // 2 bytes.  Torque Limit(Goal Torque)          | RW | ADD 1415
	add<uint16_t> (presentPosition    , 36 , "presentPosition"     , true, false);  // 2 bytes.  Present Position                   | R  | -
	add<uint16_t> (presentSpeed       , 38 , "presentSpeed"        , true, false);  // 2 bytes.  Present Speed                      | R  | -
	add<uint16_t> (presentLoad        , 40 , "presentLoad"         , true, false);  // 2 bytes.  Present Load                       | R  | -
	add<uint8_t> (presentVoltage      , 42 , "presentVoltage"      , true, false);  // 1 bytes.  Present Voltage                    | R  | -
	add<uint8_t> (presentTemperature  , 43 , "presentTemperature"  , true, false);  // 1 bytes.  Present Temperature                | R  | -
	add<uint8_t> (registered          , 44 , "registered"          , true, false);  // 1 bytes.  If Instruction is registered       | R  | 0
	add<uint8_t> (moving              , 46 , "moving"              , true, false);  // 1 bytes.  Movement Status                    | R  | 0
	add<uint8_t> (lock                , 47 , "lock"                , true, false);  // 1 bytes.  Locking EEPROM                     | RW | 0
	add<uint16_t> (punch              , 48 , "punch"               , false, false); // 2 bytes.  Minimum Current Threshold          | RW | 32
	
}
