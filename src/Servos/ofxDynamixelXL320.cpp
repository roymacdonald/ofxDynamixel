//
//  ofxDynamixelXL320.cpp
//  example
//
//  Created by Roy Macdonald on 7/26/18.
//
//

#include "ofxDynamixelXL320.h"

ofxDynamixel::XL320::XL320(){
	//	std::cout << __PRETTY_FUNCTION__ << std::endl;
	add<uint8_t >(firmwareVersion     ,  2 , "firmwareVersion"                        , true  , true);
	add<uint8_t >(id                  ,  3 , "id"                  , 1    , 0 , 252   , false , true);
	add<uint8_t >(baudRate            ,  4 , "baudRate"            , 3    , 0 ,    3  , false , true);
	add<uint8_t >(returnDelayTime     ,  5 , "returnDelayTime"     , 250  , 0 , 254   , false , true);
	add<uint16_t>(cwAngleLimit        ,  6 , "cwAngleLimit"        , 0    , 0 , 1023  , false , true);
	add<uint16_t>(ccwAngleLimit       ,  8 , "ccwAngleLimit"       , 1023 , 0 , 1023  , false , true);

	
	
	add<uint8_t>(controlMode          , 11 , "controlMode"         , 2    , 1  , 2    , false, true); // 1 bytes. Control Mode                        RW 2    , 1  , 2
	add<uint8_t>(temperatureLimit     , 12 , "temperatureLimit"    , 65   , 0  , 150  , false, true); // 1 bytes. Maximum Internal Temperature Limit  RW 65   , 0  , 150
	add<uint8_t>(minVoltageLimit      , 13 , "minVoltageLimit"     , 60   , 50 , 250  , false, true); // 1 bytes. Minimum Input Voltage Limit         RW 60   , 50 , 250
	add<uint8_t>(maxVoltageLimit      , 14 , "maxVoltageLimit"     , 90   , 50 , 250  , false, true); // 1 bytes. Maximum Input Voltage Limit         RW 90   , 50 , 250
	add<uint16_t>(maxTorque           , 15 , "maxTorque"           , 1023 , 0  , 1023 , false, true); // 2 bytes. Maximun Torque                      RW 1023 , 0  , 1023
	add<uint8_t>(statusReturnLevel    , 17 , "statusReturnLevel"   , 2    , 0  , 2    , false, true); // 1 bytes. Select Types of Status Return       RW 2    , 0  , 2
	add<uint8_t>(shutdown             , 18 , "shutdown"            , 3    , 0  , 7    , false, true); // 1 bytes. Shutdown Error Information          RW 3    , 0  , 7
	
	add<uint8_t>(torqueEnabled        , 24 , "torqueEnable"        , 0    , 0  , 1    , false, false); // 1 bytes. Motor Torque On/Off                 RW 0    , 0  , 1
	add<uint8_t>(led                  , 25 , "led"                 , 0    , 0  , 7    , false, false); // 1 bytes. Status LED On/Off                   RW 0    , 0  , 7
	add<uint8_t>(dGain                , 27 , "dGain"               , 0    , 0  , 254  , false, false); // 1 bytes. Derivative Gain                     RW 0    , 0  , 254
	add<uint8_t>(iGain                , 28 , "iGain"               , 0    , 0  , 254  , false, false); // 1 bytes. Integral Gain                       RW 0    , 0  , 254
	add<uint8_t>(pGain                , 29 , "pGain"               , 32   , 0  , 254  , false, false); // 1 bytes. Proportional Gain                   RW 32   , 0  , 254
	add<uint16_t>(goalPosition        , 30 , "goalPosition"        , 0    , 0  , 1023 , false, false); // 2 bytes. Desired Position                    RW -    , 0  , 1023
	add<uint16_t>(goalSpeed           , 32 , "goalSpeed"           , 0    , 0  , 2047 , false, false); // 2 bytes. Moving Speed(Moving Velocity)       RW -    , 0  , 2047
	add<uint16_t>(torqueLimit         , 35 , "torqueLimit"         , 0    , 0  , 1023 , false, false); // 2 bytes. Torque Limit(Goal Torque)           RW -    , 0  , 1023
	add<uint16_t>(punch               , 51 , "punch"               , 32   , 0  , 1023 , false, false); // 2 bytes. Minimum Current Threshold           RW 32   , 0  , 1023
	add<uint16_t>(presentPosition     , 37 , "presentPosition"     , 0    , 0  , 1023 , true, false);  // 2 bytes. Present Position                    R
	add<uint16_t>(presentSpeed        , 39 , "presentSpeed"        , 0    , 0  , 2047 , true, false);  // 2 bytes. Present Speed                       R
	add<uint16_t>(presentLoad         , 41 , "presentLoad"         , 0    , 0  , 2047 , true, false);  // 2 bytes. Present Load                        R
	add<uint8_t>(presentVoltage       , 45 , "presentVoltage"                         , true, false);  // 1 bytes. Present Voltage                     R
	add<uint8_t>(presentTemperature   , 46 , "presentTemperature"                     , true, false);  // 1 bytes. Present Temperature                 R
	add<uint8_t>(registered           , 47 , "registered"                             , true, false);  // 1 bytes. If Instruction is registered        R
	add<uint8_t>(moving               , 49 , "moving"              , 0    , 0  , 1    , true, false);  // 1 bytes. Movement Status                     R
	add<uint8_t>(hardwareErrorStatus  , 50 , "hardwareErrorStatus" , true, false);                     // 1 bytes. Hardware Error Status               R	
	
}
