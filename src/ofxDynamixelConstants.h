/*!
 * \file	ofRegister.h
 *
 * \brief	Declares the of registry class.
*/

#pragma once

#include <inttypes.h>

/*!
 * \enum	ofRegister enum
 *
 * \brief	Values that represent of registries.
 *
 * \author  Abdessalam Ghiouar
 * \version 0.1
 * \date	April 25, 2017
 */
namespace ofxDynamixel {
	
	enum ResetOption : uint8_t{
		RESET_ALL = 0xFF,// reset all values
		RESET_ALL_BUT_ID = 0x01,// for reset all values except ID 
		RESET_ALL_BUT_ID_AND_BAUD = 0x02// reset all values except ID and Baudrate
	};
struct XL320 {
		static const uint16_t MODEL_NUMBER            =  0;    //       2 bytes. Model Number                        R  
		static const uint16_t FIRMWARE_VERSION        =  2;    //       1 bytes. Firmware Version                    R  
		static const uint16_t ID                      =  3;    //       1 bytes. DYNAMIXEL ID                        RW  0 - 252  
		static const uint16_t BAUD_RATE               =  4;    //       1 bytes. Communication Speed                 RW  0 -  3   
		static const uint16_t RETURN_DELAY_TIME       =  5;    //       1 bytes. Response Delay Time                 RW  0 - 254  
		static const uint16_t CW_ANGLE_LIMIT          =  6;    //       2 bytes. Clockwise Angle Limit               RW  0 - 1023 
		static const uint16_t CCW_ANGLE_LIMIT         =  8;    //       2 bytes. Counter_Clockwise Angle Limit       RW  0 - 1023 
		static const uint16_t CONTROL_MODE            = 11;    //       1 bytes. Control Mode                        RW  1 -  2   
		static const uint16_t TEMPERATURE_LIMIT       = 12;    //       1 bytes. Maximum Internal Temperature Limit  RW  0 - 150  
		static const uint16_t MIN_VOLTAGE_LIMIT       = 13;    //       1 bytes. Minimum Input Voltage Limit         RW  50 - 250  
		static const uint16_t MAX_VOLTAGE_LIMIT       = 14;    //       1 bytes. Maximum Input Voltage Limit         RW  50 - 250  
		static const uint16_t MAX_TORQUE              = 15;    //       2 bytes. Maximun Torque                      RW  0 - 1023 
		static const uint16_t STATUS_RETURN_LEVEL     = 17;    //       1 bytes. Select Types of Status Return       RW  0 -  2   
		static const uint16_t SHUTDOWN                = 18;    //       1 bytes. Shutdown Error Information          RW  0 -  7   
		static const uint16_t TORQUE_ENABLE           = 24;    //       1 bytes. Motor Torque On/Off                 RW   0 -  1  
		static const uint16_t LED                     = 25;    //       1 bytes. Status LED On/Off                   RW   0 -  7  
		static const uint16_t D_GAIN                  = 27;    //       1 bytes. Derivative Gain                     RW   0 - 254 
		static const uint16_t I_GAIN                  = 28;    //       1 bytes. Integral Gain                       RW   0 - 254 
		static const uint16_t P_GAIN                  = 29;    //       1 bytes. Proportional Gain                   RW   0 - 254 
		static const uint16_t GOAL_POSITION           = 30;    //       2 bytes. Desired Position                    RW   0 - 1023
		static const uint16_t MOVING_SPEED            = 32;    //       2 bytes. Moving Speed(Moving Velocity)       RW   0 - 2047
		static const uint16_t TORQUE_LIMIT            = 35;    //       2 bytes. Torque Limit(Goal Torque)           RW   0 - 1023
		static const uint16_t PUNCH                   = 51;    //       2 bytes. Minimum Current Threshold           RW   0 - 1023
		static const uint16_t PRESENT_POSITION        = 37;    //       2 bytes. Present Position                    R    
		static const uint16_t PRESENT_SPEED           = 39;    //       2 bytes. Present Speed                       R   
		static const uint16_t PRESENT_LOAD            = 41;    //       2 bytes. Present Load                        R   
		static const uint16_t PRESENT_VOLTAGE         = 45;    //       1 bytes. Present Voltage                     R   
		static const uint16_t PRESENT_TEMPERATURE     = 46;    //       1 bytes. Present Temperature                 R   
		static const uint16_t REGISTERED              = 47;    //       1 bytes. If Instruction is registered        R   
		static const uint16_t MOVING                  = 49;    //       1 bytes. Movement Status                     R   
		static const uint16_t HARDWARE_ERROR_STATUS   = 50;    //       1 bytes. Hardware Error Status               R    
};

	
struct AX12{
		static const uint16_t MODEL_NUMBER = 			0;   //     | 2 bytes.  Model Number                       | R      | 12            
		static const uint16_t FIRMWARE_VERSION = 		2;   //     | 1 bytes.  Firmware Version                   | R      | -             
		static const uint16_t ID =		 				3;   //     | 1 bytes.  DYNAMIXEL ID                       | RW     | 1             
		static const uint16_t BAUD_RATE = 				4;   //     | 1 bytes.  Communication Speed                | RW     | 1             
		static const uint16_t RETURN_DELAY_TIME = 		5;   //     | 1 bytes.  Response Delay Time                | RW     | 250           
		static const uint16_t CW_ANGLE_LIMIT = 			6;   //     | 2 bytes.  Clockwise Angle Limit              | RW     | 0             
		static const uint16_t CCW_ANGLE_LIMIT = 		8;   //     | 2 bytes.  Counter-Clockwise Angle Limit      | RW     | 1023          
		static const uint16_t TEMPERATURE_LIMIT = 		11;  //     | 1 bytes.  Maximum Internal Temperature Limit | RW     | 70            
		static const uint16_t MIN_VOLTAGE_LIMIT = 		12;  //     | 1 bytes.  Minimum Input Voltage Limit        | RW     | 60            
		static const uint16_t MAX_VOLTAGE_LIMIT = 		13;  //     | 1 bytes.  Maximum Input Voltage Limit        | RW     | 140           
		static const uint16_t MAX_TORQUE = 				14;  //     | 2 bytes.  Maximun Torque                     | RW     | 1023          
		static const uint16_t STATUS_RETURN_LEVEL =	    16;  //     | 1 bytes.  Select Types of Status Return      | RW     | 2             
		static const uint16_t ALARM_LED = 				17;  //     | 1 bytes.  LED for Alarm                      | RW     | 36            
		static const uint16_t SHUTDOWN = 				18;  //     | 1 bytes.  Shutdown Error Information         | RW     | 36            
		static const uint16_t TORQUE_ENABLE = 			24;  //     | 1 bytes.  Motor Torque On/Off                | RW     | 0             
		static const uint16_t LED = 	 				25;  //     | 1 bytes.  Status LED On/Off                  | RW     | 0             
		static const uint16_t CW_COMPLIANCE_MARGIN = 	26;  //     | 1 bytes.  CW Compliance Margin               | RW     | 1             
		static const uint16_t CCW_COMPLIANCE_MARGIN = 	27;  //     | 1 bytes.  CCW Compliance Margin              | RW     | 1             
		static const uint16_t CW_COMPLIANCE_SLOPE = 	28;  //     | 1 bytes.  CW Compliance Slope                | RW     | 32            
		static const uint16_t CCW_COMPLIANCE_ALOPE = 	29;  //     | 1 bytes.  CCW Compliance Slope               | RW     | 32            
		static const uint16_t GOAL_POSITION = 			30;  //     | 2 bytes.  Target Position                    | RW     | -             
		static const uint16_t MOVING_SPEED = 			32;  //     | 2 bytes.  Moving Speed                       | RW     | -             
		static const uint16_t TORQUE_LIMIT = 			34;  //     | 2 bytes.  Torque Limit(Goal Torque)          | RW     | ADD 14_15 
		static const uint16_t PRESENT_POSITION = 		36;  //     | 2 bytes.  Present Position                   | R      | -             
		static const uint16_t PRESENT_SPEED = 			38;  //     | 2 bytes.  Present Speed                      | R      | -             
		static const uint16_t PRESENT_LOAD = 			40;  //     | 2 bytes.  Present Load                       | R      | -             
		static const uint16_t PRESENT_VOLTAGE = 		42;  //     | 1 bytes.  Present Voltage                    | R      | -             
		static const uint16_t PRESENT_TEMPERATURE = 	43;  //     | 1 bytes.  Present Temperature                | R      | -             
		static const uint16_t REGISTERED = 				44;  //     | 1 bytes.  If Instruction is registered       | R      | 0             
		static const uint16_t MOVING = 				 	46;  //     | 1 bytes.  Movement Status                    | R      | 0             
		static const uint16_t LOCK = 				    47;  //     | 1 bytes.  Locking EEPROM                     | RW     | 0             
		static const uint16_t PUNCH = 				    48; //     | 2 bytes.  Minimum Current Threshold          | RW     | 32       
};

enum Errors : uint16_t
{
	/*! \brief	When the applied voltage is out of the range 
	 of operating voltage set in the Control Table. */
	INPUTVOLTAGE = 0,
	
	/*! \brief	 When Goal Position is written with the value that 
	 is not between CW Angle Limit and CCW Angle Limit
	 .	*/
	
	ANGLELIMIT = 1,
	/*! \brief	When the internal temperature is out of the range 
	 of operating temperature set in the Control Table
	 .	*/
	OVERHEATING = 2,
	
	/*! \brief	When the command is given beyond the range of usage. */
	RANGE = 3,
	
	/*! \brief	When the Checksum of the transmitted Instruction Packet is invalid. */
	
	CHECKSUM = 4,
	/*! \brief	When the current load cannot be controlled with the set maximum torque. */
	
	OVERLOAD = 5,
	/*! \brief	When undefined Instruction is transmitted or 
	 the Action command is delivered without the reg_write command
	 .	*/
	INSTRUCTION = 6,
	
	/*! \brief	When undefined Instruction is transmitted or 
	 the Action command is delivered without the reg_write command
	 .	*/
	NOERROR = 7,
	
};
}
