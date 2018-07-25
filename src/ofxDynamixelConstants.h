#pragma once

#include <inttypes.h>

#define ENABLE_GUI_UPDATE


namespace ofxDynamixel {
	
	enum ResetOption : uint8_t{
		RESET_ALL = 0xFF,// reset all values
		RESET_ALL_BUT_ID = 0x01,// for reset all values except ID 
		RESET_ALL_BUT_ID_AND_BAUD = 0x02// reset all values except ID and Baudrate
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
