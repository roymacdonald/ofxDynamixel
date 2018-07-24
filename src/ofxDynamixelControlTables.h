//
//  ofxDynamixelControlTables.h
//  example
//
//  Created by Roy Macdonald on 7/24/18.
//
//
#pragma once

namespace ofxDynamixel {
	class  DXLBaseRegister{
	public:
		inline static uint16_t MODEL_NUMBER(){           return 0;}    //       2 bytes. Model Number                        R  
		inline static uint16_t FIRMWARE_VERSION(){       return 2;}    //       1 bytes. Firmware Version                    R
		inline static uint16_t ID(){                     return 3;}    //       1 bytes. DYNAMIXEL ID                        RW  0 - 252
		inline static uint16_t BAUD_RATE(){              return 4;}    //       1 bytes. Communication Speed                 RW  0 -  3
		inline static uint16_t RETURN_DELAY_TIME(){      return 5;}    //       1 bytes. Response Delay Time                 RW  0 - 254
		inline static uint16_t CW_ANGLE_LIMIT(){         return 6;}    //       2 bytes. Clockwise Angle Limit               RW  0 - 1023
		inline static uint16_t CCW_ANGLE_LIMIT(){        return 8;}    //       2 bytes. Counter_Clockwise Angle Limit       RW  0 - 1023
		
		
	};
	
	class XL320: public DXLBaseRegister {
	public:
		inline static uint16_t CONTROL_MODE(){          return 11;}    //       1 bytes. Control Mode                        RW  1 -  2
		inline static uint16_t TEMPERATURE_LIMIT(){     return 12;}    //       1 bytes. Maximum Internal Temperature Limit  RW  0 - 150
		inline static uint16_t MIN_VOLTAGE_LIMIT(){     return 13;}    //       1 bytes. Minimum Input Voltage Limit         RW  50 - 250
		inline static uint16_t MAX_VOLTAGE_LIMIT(){     return 14;}    //       1 bytes. Maximum Input Voltage Limit         RW  50 - 250
		inline static uint16_t MAX_TORQUE(){            return 15;}    //       2 bytes. Maximun Torque                      RW  0 - 1023
		inline static uint16_t STATUS_RETURN_LEVEL(){   return 17;}    //       1 bytes. Select Types of Status Return       RW  0 -  2
		inline static uint16_t SHUTDOWN(){              return 18;}    //       1 bytes. Shutdown Error Information          RW  0 -  7
		inline static uint16_t TORQUE_ENABLE(){         return 24;}    //       1 bytes. Motor Torque On/Off                 RW   0 -  1
		inline static uint16_t LED(){                   return 25;}    //       1 bytes. Status LED On/Off                   RW   0 -  7
		inline static uint16_t D_GAIN(){                return 27;}    //       1 bytes. Derivative Gain                     RW   0 - 254
		inline static uint16_t I_GAIN(){                return 28;}    //       1 bytes. Integral Gain                       RW   0 - 254
		inline static uint16_t P_GAIN(){                return 29;}    //       1 bytes. Proportional Gain                   RW   0 - 254
		inline static uint16_t GOAL_POSITION(){         return 30;}    //       2 bytes. Desired Position                    RW   0 - 1023
		inline static uint16_t MOVING_SPEED(){          return 32;}    //       2 bytes. Moving Speed(Moving Velocity)       RW   0 - 2047
		inline static uint16_t TORQUE_LIMIT(){          return 35;}    //       2 bytes. Torque Limit(Goal Torque)           RW   0 - 1023
		inline static uint16_t PUNCH(){                 return 51;}    //       2 bytes. Minimum Current Threshold           RW   0 - 1023
		inline static uint16_t PRESENT_POSITION(){      return 37;}    //       2 bytes. Present Position                    R
		inline static uint16_t PRESENT_SPEED(){         return 39;}    //       2 bytes. Present Speed                       R
		inline static uint16_t PRESENT_LOAD(){          return 41;}    //       2 bytes. Present Load                        R
		inline static uint16_t PRESENT_VOLTAGE(){       return 45;}    //       1 bytes. Present Voltage                     R
		inline static uint16_t PRESENT_TEMPERATURE(){   return 46;}    //       1 bytes. Present Temperature                 R
		inline static uint16_t REGISTERED(){            return 47;}    //       1 bytes. If Instruction is registered        R
		inline static uint16_t MOVING(){                return 49;}    //       1 bytes. Movement Status                     R
		inline static uint16_t HARDWARE_ERROR_STATUS(){ return 50;}    //       1 bytes. Hardware Error Status               R
		
		//not maent to be used
		inline static uint16_t CW_COMPLIANCE_MARGIN(){  return 0;}
		inline static uint16_t CCW_COMPLIANCE_MARGIN(){ return 0;}
		inline static uint16_t CW_COMPLIANCE_SLOPE(){   return 0;}
		inline static uint16_t CCW_COMPLIANCE_SLOPE(){  return 0;}
		inline static uint16_t LOCK(){                  return 0;}
		
		
	};
	
	
	class AX12: public DXLBaseRegister {
	public:
		inline static uint16_t TEMPERATURE_LIMIT(){     return 11;}  //       | 1 bytes.  Maximum Internal Temperature Limit | RW | 70
		inline static uint16_t MIN_VOLTAGE_LIMIT(){     return 12;}  //       | 1 bytes.  Minimum Input Voltage Limit        | RW | 60
		inline static uint16_t MAX_VOLTAGE_LIMIT(){     return 13;}  //       | 1 bytes.  Maximum Input Voltage Limit        | RW | 140
		inline static uint16_t MAX_TORQUE(){            return 14;}  //       | 2 bytes.  Maximun Torque                     | RW | 1023
		inline static uint16_t STATUS_RETURN_LEVEL(){   return 16;}  //       | 1 bytes.  Select Types of Status Return      | RW | 2
		inline static uint16_t ALARM_LED(){             return 17;}  //       | 1 bytes.  LED for Alarm                      | RW | 36
		inline static uint16_t SHUTDOWN(){              return 18;}  //       | 1 bytes.  Shutdown Error Information         | RW | 36
		inline static uint16_t TORQUE_ENABLE(){         return 24;}  //       | 1 bytes.  Motor Torque On/Off                | RW | 0
		inline static uint16_t LED(){                   return 25;}  //       | 1 bytes.  Status LED On/Off                  | RW | 0
		inline static uint16_t CW_COMPLIANCE_MARGIN(){  return 26;}  //       | 1 bytes.  CW Compliance Margin               | RW | 1
		inline static uint16_t CCW_COMPLIANCE_MARGIN(){ return 27;}  //       | 1 bytes.  CCW Compliance Margin              | RW | 1
		inline static uint16_t CW_COMPLIANCE_SLOPE(){   return 28;}  //       | 1 bytes.  CW Compliance Slope                | RW | 32
		inline static uint16_t CCW_COMPLIANCE_SLOPE(){  return 29;}  //       | 1 bytes.  CCW Compliance Slope               | RW | 32
		inline static uint16_t GOAL_POSITION(){         return 30;}  //       | 2 bytes.  Target Position                    | RW | -
		inline static uint16_t MOVING_SPEED(){          return 32;}  //       | 2 bytes.  Moving Speed                       | RW | -
		inline static uint16_t TORQUE_LIMIT(){          return 34;}  //       | 2 bytes.  Torque Limit(Goal Torque)          | RW | ADD 14_15
		inline static uint16_t PRESENT_POSITION(){      return 36;}  //       | 2 bytes.  Present Position                   | R  | -
		inline static uint16_t PRESENT_SPEED(){         return 38;}  //       | 2 bytes.  Present Speed                      | R  | -
		inline static uint16_t PRESENT_LOAD(){          return 40;}  //       | 2 bytes.  Present Load                       | R  | -
		inline static uint16_t PRESENT_VOLTAGE(){       return 42;}  //       | 1 bytes.  Present Voltage                    | R  | -
		inline static uint16_t PRESENT_TEMPERATURE(){   return 43;}  //       | 1 bytes.  Present Temperature                | R  | -
		inline static uint16_t REGISTERED(){            return 44;}  //       | 1 bytes.  If Instruction is registered       | R  | 0
		inline static uint16_t MOVING(){                return 46;}  //       | 1 bytes.  Movement Status                    | R  | 0
		inline static uint16_t LOCK(){                  return 47;}  //       | 1 bytes.  Locking EEPROM                     | RW | 0
		inline static uint16_t PUNCH(){                 return 48;}  //       | 2 bytes.  Minimum Current Threshold          | RW | 32
		
		//not meant to be used
		inline static uint16_t CONTROL_MODE(){          return 0;}    
		inline static uint16_t D_GAIN(){                return 0;}    
		inline static uint16_t I_GAIN(){                return 0;}    
		inline static uint16_t P_GAIN(){                return 0;}    
		inline static uint16_t HARDWARE_ERROR_STATUS(){ return 0;}
	};
}
