//
//  ofxDynamixelXL430.cpp
//  example
//
//  Created by Roy Macdonald on 7/27/18.
//
//

#include "ofxDynamixelXL430.h"


ofxDynamixel::XL430::XL430(){
	
	//
	add<uint32_t>( modelInformation      , 2,  "modelInformation"                                 ,  true,  true);  // "Model Information"                               | R  |       |
	add<uint8_t>( firmwareVersion        , 6,  "firmwareVersion"                                 ,   true,  true);  // "Firmware Version"                                | R  |       |
	add<uint8_t>( id                     , 7   , "id"                    , 1     , 0     , 252   , false , true );  // "DYNAMIXEL ID"                                    | RW | 1     |
	add<uint8_t>( baudRate               , 8   , "baudRate"              , 1     , 0     , 7     , false , true );  // "Communication Speed"                             | RW | 1     |
	add<uint8_t>( returnDelayTime        , 9   , "returnDelayTime"       , 250   , 0     , 254   , false , true );  // "Response Delay Time"                             | RW | 250   |
	add<uint8_t>( driveMode              , 10  , "driveMode"             , 0     , 0     ,       1, false , true );  // "Default Rotation Direction"                      | RW | 0     |
	add<uint8_t>( operatingMode          , 11  , "operatingMode"         , 3     , 0     ,     16  , false , true );  // "Operating Mode"                                  | RW | 3     |//list
	add<uint8_t>( secondaryShadowId      , 12  , "secondaryShadowId"     , 255   , 0     , 255   , false , true );  // "Secondary(Shadow ID"                             | RW | 255   |
	add<uint8_t>( protocolVersion        , 13  , "protocolVersion"       , 2     , 0     , 2     , false , true );  // "Protocol Version"                                | RW | 2     |
	add<uint32_t>( homingOffset          , 20  , "homingOffset"          , 0     , 0     , 2048  , false , true );  // "Home Position Offset"                            | RW | 0     |
	add<uint32_t>( movingThreshold       , 24  , "movingThreshold"       , 10    , 0     , 1023  , false , true );  // "Velocity Threshold for Movement Detection"       | RW | 10    |
	add<uint8_t>( temperatureLimit       , 31  , "temperatureLimit"      , 72    , 0     , 100   , false , true );  // "Maximum Internal Temperature Limit"              | RW | 72    |
	add<uint16_t>( maxVoltageLimit       , 32  , "maxVoltageLimit"       , 140   , 60    , 140   , false , true );  // "Maximum Input Voltage Limit"                     | RW | 140   |
	add<uint16_t>( minVoltageLimit       , 34  , "minVoltageLimit"       , 60    , 60    , 140   , false , true );  // "Minimum Input Voltage Limit"                     | RW | 60    |
	add<uint16_t>( pwmLimit              , 36  , "pwmLimit"              , 885   , 0     , 885   , false , true );  // "Maximum PWM Limit"                               | RW | 885   |
	add<uint32_t>( accelerationLimit     , 40  , "accelerationLimit"     , 32767 , 0     , 32767 , false , true );  // "Maximum Accleration Limit"                       | RW | 32767 |
	add<uint32_t>( velocityLimit         , 44  , "velocityLimit"         , 415   , 0     , 1023  , false , true );  // "Maximum Velocity Limit"                          | RW | 415   |
	add<uint32_t>( maxPositionLimit      , 48  , "maxPositionLimit"      , 4095  , 0     , 4095  , false , true );  // "Maximum Position Limit"                          | RW | 4                                                                         , 095 |
	add<uint32_t>( minPositionLimit      , 52  , "minPositionLimit"      , 0     , 0     , 4095  , false , true );  // "Minimum Position Limit"                          | RW | 0     |
	add<uint8_t>( shutdown               , 63  , "shutdown"              , 52    , 0     , 254   , false , true );  // "Shutdown Error Information"                      | RW | 52    |//bitfield
	
	add<uint8_t> (  statusReturnLevel     , 68  , "statusReturnLevel"     , 2    , 0     , 2     , false , false );  // "Select Types of Status Return                    | RW | 2     |
	addBool      (  torqueEnabled         , 64  , "torqueEnable"          ,false                 , false , false );  // "Motor Torque On/Off                              | RW | 0     |
	addBool      (  led                   , 65  , "led"                   ,false                 , false , false );  // "Status LED On/Off                                | RW | 0     |
	addBool      (  registeredInstruction , 69  , "registeredInstruction" ,false                 , true  , false );  // "Check Reception of Instruction                   | R  | 0     |
	add<uint8_t >(  hardwareErrorStatus   , 70  , "hardwareErrorStatus"   ,0,0,255                 , true  , false );  // "Hardware Error Status //  bitfield                            | R  | 0     |//BITFIELD
	add<uint16_t>(  velocityIGain         , 76  , "velocityIGain"         , 1000 , 0     , 16383 , false , false );  // "I Gain of Velocity                               | RW | 1000  |
	add<uint16_t>(  velocityPGain         , 78  , "velocityPGain"         , 100  , 0     , 16383 , false , false );  // "P Gain of Velocity                               | RW | 100   |
	add<uint16_t>(  positionDGain         , 80  , "positionDGain"         , 4000 , 0     , 16383 , false , false );  // "D Gain of Position                               | RW | 4000  |
	add<uint16_t>(  positionIGain         , 82  , "positionIGain"         , 0    , 0     , 16383 , false , false );  // "I Gain of Position                               | RW | 0     |
	add<uint16_t>(  positionPGain         , 84  , "positionPGain"         , 640  , 0     , 16383 , false , false );  // "P Gain of Position                               | RW | 640   |
	add<uint16_t>(  feedforward2ndGain    , 88  , "feedforward2ndGain"    , 0    , 0     , 16383 , false , false );  // "2nd Gain of FeedForward                          | RW | 0     |
	add<uint16_t>(  feedforward1stGain    , 90  , "feedforward1stGain"    , 0    , 0     , 16383 , false , false );  // "1st Gain of FeedForward                          | RW | 0     |
	add<uint8_t> (  busWatchdog           , 98  , "busWatchdog"           , 0    , 0     , 255   , false , false );  // "DYNAMIXEL Bus Watchdog                           | RW | 0     |// PONER ATENCIAL AL WATCHDOG/ PONER EN 0 PARA DESACTIVAR/RESETAR
	add<uint16_t>(  goalPwm               , 100 , "goalPwm"               , 0    , -885  , 885   , false , false );  // "Desired PWM Value                                | RW |       |
	add<uint32_t>(  goalVelocity          , 104 , "goalVelocity"          , 0    , -1023 , 1023  , false , false );  // "Desired Velocity Value                           | RW |       |
	add<uint32_t>(  profileAcceleration   , 108 , "profileAcceleration"   , 0    , 0     , 32767 , false , false );  // "Acceleration Value of Profile                    | RW | 0     |
	add<uint32_t>(  profileVelocity       , 112 , "profileVelocity"       , 0    , 0     , 1023  , false , false );  // "Velocity Value of Profile                        | RW | 0     |
	add<uint32_t>(  goalPosition          , 116 , "goalPosition"          , 0    , 0     , 4095  , false , false );  // "Desired Position Value                           | RW |       |
	add<uint16_t>(  realtimeTick          , 120 , "realtimeTick"          , 0    , 0     , 32767 , true  , false );  // "Count Time in millisecond                        | R  |       |
	addBool      (  moving                , 122 , "moving"                ,false                 , true  , false );  // "Movement Status                                  | R  | 0     |
	add<uint8_t> (  movingStatus          , 123 , "movingStatus"          , 0    , 0     , 255   , true  , false );  // "Detailed Information of Movement Status          | R  | 0     |//bitfield
	add<uint16_t>(  presentPwm            , 124 , "presentPwm"            , 0    , -855  , 885   , true  , false );  // "Present PWM Value                                | R  |       |
	add<uint16_t>(  presentLoad           , 126 , "presentLoad"           , 0    , -1000 , 1000  , true  , false );  // "Present Load Value                               | R  |       |
	add<uint32_t>(  presentVelocity       , 128 , "presentVelocity"       , 0    , -1023 , 1023  , true  , false );  // "Present Velocity Value                           | R  |       |
	add<uint32_t>(  presentPosition       , 132 , "presentPosition"       , 0    , 0     , 4095  , true  , false );  // "Present Position Value                           | R  |       |//-2                                                              , 147 , 483 , 648 ~ 2 , 147 , 483 , 647 CUANDO NO ES POSITION CONTROL O TORQUE OFF
	add<uint32_t>(  velocityTrajectory    , 136 , "velocityTrajectory"    , 0    , 0     , 1023  , true  , false );  // "Desired Velocity Trajectory Generated by Profile | R  |       |
	add<uint32_t>(  positionTrajectory    , 140 , "positionTrajectory"    , 0    , 0     , 4095  , true  , false );  // "Desired Position Trajectory Generated by Profile | R  |       |
	add<uint16_t>(  presentInputVoltage   , 144 , "presentInputVoltage"   , 0    , 60    , 140   , true  , false );  // "Present Input Voltage                            | R  |       |
	add<uint8_t> (  presentTemperature    , 146 , "presentTemperature"    , 0    , 0     , 100   , true  , false );  // "Present Internal Temperature                     | R  |       |
	
}
