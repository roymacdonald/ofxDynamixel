//
//  ofxDynamixelXL430.hpp
//  example
//
//  Created by Roy Macdonald on 7/27/18.
//
//

#pragma once

#include "ofxDynamixelControlTables.h"

namespace ofxDynamixel {
	
	class XL430: public DXLBaseControlTable {
	public:
		
		XL430();		
		
		virtual uint32_t getResolution() override {return 4096;}
		
		virtual std::string getModelName() override{ return  "XL430";}

//| Address | Size<br>(Byte) | Data Name                  | Description                                      | Access | Initial<br />Value |
		
// Reg16 modelNumber;       // 0, "Model Number"                              | R  | 1060  |
Reg32 modelInformation;  // 2, "Model Information"                         | R  |       |
Reg8 firmwareVersion;   // 6, "Firmware Version"                          | R  |       |
Reg8 id;                // 7, "DYNAMIXEL ID"                              | RW | 1     |
Reg8 baudRate;          // 8, "Communication Speed"                       | RW | 1     |
Reg8 returnDelayTime;   // 9, "Response Delay Time"                       | RW | 250   |
Reg8 driveMode;         // 10, "Default Rotation Direction"                | RW | 0     |
Reg8 operatingMode;     // 11, "Operating Mode"                            | RW | 3     |
Reg8 secondaryShadowId; // 12, "Secondary(Shadow ID"                       | RW | 255   |
Reg8 protocolVersion;   // 13, "Protocol Version"                          | RW | 2     |
Reg32 homingOffset;      // 20, "Home Position Offset"                      | RW | 0     |
Reg32 movingThreshold;   // 24, "Velocity Threshold for Movement Detection" | RW | 10    |
Reg8 temperatureLimit;  // 31, "Maximum Internal Temperature Limit"        | RW | 72    |
Reg16 maxVoltageLimit;   // 32, "Maximum Input Voltage Limit"               | RW | 140   |
Reg16 minVoltageLimit;   // 34, "Minimum Input Voltage Limit"               | RW | 60    |
Reg16 pwmLimit;          // 36, "Maximum PWM Limit"                         | RW | 885   |
Reg32 accelerationLimit; // 40, "Maximum Accleration Limit"                 | RW | 32767 |
Reg32 velocityLimit;     // 44, "Maximum Velocity Limit"                    | RW | 415   |
Reg32 maxPositionLimit;  // 48, "Maximum Position Limit"                    | RW | 4,095 |
Reg32 minPositionLimit;  // 52, "Minimum Position Limit"                    | RW | 0     |
Reg8 shutdown;          // 63, "Shutdown Error Information"                | RW | 52    |
RegBool  torqueEnabled;          // 64,  "Motor Torque On/Off                              | RW  | 0    |// ## controlTableOfRamArea
RegBool  led;                   // 65,  "Status LED On/Off                                | RW  | 0    |
Reg8  statusReturnLevel;     // 68,  "Select Types of Status Return                    | RW  | 2    |
RegBool  registeredInstruction; // 69,  "Check Reception of Instruction                   | R   | 0    |
Reg8  hardwareErrorStatus;   // 70,  "Hardware Error Status                            | R   | 0    |
Reg16  velocityIGain;         // 76,  "I Gain of Velocity                               | RW  | 1000 |
Reg16  velocityPGain;         // 78,  "P Gain of Velocity                               | RW  | 100  |
Reg16  positionDGain;         // 80,  "D Gain of Position                               | RW  | 4000 |
Reg16  positionIGain;         // 82,  "I Gain of Position                               | RW  | 0    |
Reg16  positionPGain;         // 84,  "P Gain of Position                               | RW  | 640  |
Reg16  feedforward2ndGain;    // 88,  "2nd Gain of FeedForward                          | RW  | 0    |
Reg16  feedforward1stGain;    // 90,  "1st Gain of FeedForward                          | RW  | 0    |
Reg8  busWatchdog;           // 98,  "DYNAMIXEL Bus Watchdog                           | RW  | 0    |
Reg16  goalPwm;               // 100,  "Desired PWM Value                                | RW  |      |
Reg32  goalVelocity;          // 104,  "Desired Velocity Value                           | RW  |      |
Reg32  profileAcceleration;   // 108,  "Acceleration Value of Profile                    | RW  | 0    |
Reg32  profileVelocity;       // 112,  "Velocity Value of Profile                        | RW  | 0    |
Reg32  goalPosition;          // 116,  "Desired Position Value                           | RW  |      |
Reg16  realtimeTick;          // 120,  "Count Time in millisecond                        | R   |      |
RegBool  moving;                // 122,  "Movement Status                                  | R   | 0    |
Reg8  movingStatus;          // 123,  "Detailed Information of Movement Status          | R   | 0    |
Reg16  presentPwm;            // 124,  "Present PWM Value                                | R   |      |
Reg16  presentLoad;           // 126,  "Present Load Value                               | R   |      |
Reg32  presentVelocity;       // 128,  "Present Velocity Value                           | R   |      |
Reg32  presentPosition;       // 132,  "Present Position Value                           | R   |      |
Reg32  velocityTrajectory;    // 136,  "Desired Velocity Trajectory Generated by Profile | R   |      |
Reg32  positionTrajectory;    // 140,  "Desired Position Trajectory Generated by Profile | R   |      |
Reg16  presentInputVoltage;   // 144,  "Present Input Voltage                            | R   |      |
Reg8  presentTemperature;    // 146,  "Present Internal Temperature                     | R   |      |

// | 168 | 2   | indirectAddress       | Indirect Address 1                               | RW  | 224  |
// | 170 | 2   | indirectAddress       | Indirect Address 2                               | RW  | 225  |
// | 172 | 2   | indirectAddress       | Indirect Address 3                               | RW  | 226  |
// | ... | ... | ...                   | ...                                              | ... | ...  |
// | 218 | 2   | indirectAddress       | Indirect Address 26                              | RW  | 249  |
// | 220 | 2   | indirectAddress       | Indirect Address 27                              | RW  | 250  |
// | 222 | 2   | indirectAddress       | Indirect Address 28                              | RW  | 251  |
// | 224 | 1   | indirectData          | Indirect Data 1                                  | RW  | 0    |
// | 225 | 1   | indirectData          | Indirect Data 2                                  | RW  | 0    |
// | 226 | 1   | indirectData          | Indirect Data 3                                  | RW  | 0    |
// | ... | ... | ...                   | ...                                              | ... | ...  |
// | 249 | 1   | indirectData          | Indirect Data 26                                 | RW  | 0    |
// | 250 | 1   | indirectData          | Indirect Data 27                                 | RW  | 0    |
// | 251 | 1   | indirectData          | Indirect Data 28                                 | RW  | 0    |
// | 578 | 2   | indirectAddress       | Indirect Address 29                              | RW  | 634  |
// | 580 | 2   | indirectAddress       | Indirect Address 30                              | RW  | 635  |
// | 582 | 2   | indirectAddress       | Indirect Address 31                              | RW  | 636  |
// | ... | ... | ...                   | ...                                              | ... | ...  |
// | 628 | 2   | indirectAddress       | Indirect Address 54                              | RW  | 659  |
// | 630 | 2   | indirectAddress       | Indirect Address 55                              | RW  | 660  |
// | 632 | 2   | indirectAddress       | Indirect Address 56                              | RW  | 661  |
// | 634 | 1   | indirectData          | Indirect Data 29                                 | RW  | 0    |
// | 635 | 1   | indirectData          | Indirect Data 30                                 | RW  | 0    |
// | 636 | 1   | indirectData          | Indirect Data 31                                 | RW  | 0    |
// | ... | ... | ...                   | ...                                              | ... | ...  |
// | 659 | 1   | indirectData          | Indirect Data 54                                 | RW  | 0    |
// | 660 | 1   | indirectData          | Indirect Data 55                                 | RW  | 0    |
// | 661 | 1   | indirectData          | Indirect Data 56                                 | RW  | 0    |


		
	};
	
}
