//
//  ofxDynamixelBaseServo.hpp
//  example
//
//  Created by Roy Macdonald on 7/23/18.
//
//


#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "ofxDynamixelConnection.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelServoGui.h"
#include "ofxGui.h"
namespace ofxDynamixel {
template<typename Model>
class ServoGui;

	template<typename Model>
	class Servo: public  std::enable_shared_from_this<Servo<Model>> {
	public:
		
		Model model;
		
		
		Servo(){
		}
		Servo(int id, std::shared_ptr<Connection> connection);
		
		virtual ~Servo(){}
		Servo(Servo&);
		Servo& operator=(Servo&);
		
		virtual void setup(int id, std::shared_ptr<Connection> connection);

		std::shared_ptr<Connection> getConnection();
		void setConnection(std::shared_ptr<Connection> connection);
		
		
		bool ping();		
		bool reset(ResetOption option = RESET_ALL_BUT_ID_AND_BAUD);
		bool initialize();		
		void stop();
		bool reboot();
		
		void moveWithAcceleration(int goalPosition, int movingSpeed, int accelerationSpeed);
		
		
		void readData1B(uint16_t address);
		void readData2B(uint16_t address);
		void readData4B(uint16_t address);
		int writeData1B(int address, uint8_t dataChange);
		int writeData2B(int address, uint16_t dataChange);
		int writeData4B(int address, uint32_t dataChange);
		
		
		uint16_t   getModelNumber();         // Model Number                        R
		uint8_t    getFirmwareVersion();     // Firmware Version                    R
		uint8_t    getId();					 // returns the locally stored id
		uint8_t    getIdFromServo();         // DYNAMIXEL ID                        RW  0 - 252
		uint8_t    getBaudRate();            // Communication Speed                 RW  0 -  3
		uint8_t    getReturnDelayTime();     // Response Delay Time                 RW  0 - 254
		uint16_t   getCwAngleLimit();        // Clockwise Angle Limit               RW  0 - 1023
		uint16_t   getCcwAngleLimit();       // Counter_Clockwise Angle Limit       RW  0 - 1023
		uint8_t    getControlMode();         // Control Mode                        RW  1 -  2
		uint8_t    getTemperatureLimit();    // Maximum Internal Temperature Limit  RW  0 - 150
		uint8_t    getMinVoltageLimit();     // Minimum Input Voltage Limit         RW  50 - 250
		uint8_t    getMaxVoltageLimit();     // Maximum Input Voltage Limit         RW  50 - 250
		uint16_t   getMaxTorque();           // Maximun Torque                      RW  0 - 1023
		uint8_t    getStatusReturnLevel();   // Select Types of Status Return       RW  0 -  2
		uint8_t    getShutdown();            // Shutdown Error Information          RW  0 -  7
		bool       getTorqueEnabled();       // Motor Torque On/Off                 RW   0 -  1
		uint8_t    getLedStatus();           // Status LED On/Off                   RW   0 -  7
		uint8_t    getDGain();               // Derivative Gain                     RW   0 - 254
		uint8_t    getIGain();               // Integral Gain                       RW   0 - 254
		uint8_t    getPGain();               // Proportional Gain                   RW   0 - 254
		uint16_t   getGoalPosition();        // Desired Position                    RW   0 - 1023
		uint16_t   getGoalSpeed();           // Moving Speed(Moving Velocity)       RW   0 - 2047
		uint16_t   getTorqueLimit();         // Torque Limit(Goal Torque)           RW   0 - 1023
		uint16_t   getPunch();               // Minimum Current Threshold           RW   0 - 1023
		uint16_t   getPresentPosition();     // Present Position                    R
		uint16_t   getPresentSpeed();        // Present Speed                       R
		uint16_t   getPresentLoad();         // Present Load                        R
		uint8_t    getPresentVoltage();      // Present Voltage                     R
		uint8_t    getPresentTemperature();  // Present Temperature                 R
		uint8_t    getRegistered();          // If Instruction is registered        R
		uint8_t    getMoving();              // Movement Status                     R
		uint8_t    getHardwareErrorStatus(); // Hardware Error Status               R
		
		
		
		bool setId(uint8_t );				// range 0 -  252
		bool setBaudRate(const uint8_t& );			// range 0 -    3   
		bool setReturnDelayTime(const uint8_t& );	// range 0 -  254  
		bool setCwAngleLimit(const uint16_t& );		// range 0 - 1023 
		bool setCcwAngleLimit(const uint16_t& );	// range 0 - 1023 
		bool setControlMode(const uint8_t& );		// range 1 -    2   
		bool setTemperatureLimit(const uint8_t& );	// range 0 -  150  
		bool setMinVoltageLimit(const uint8_t& );	// range 50 - 250  
		bool setMaxVoltageLimit(const uint8_t& );	// range 50 - 250  
		bool setMaxTorque(const uint16_t& );		// range 0 - 1023 
		bool setStatusReturnLevel(const uint8_t& );	// range 0 -    2   
		bool setShutdown(const uint8_t& );			// range 0 -    7   
		bool setTorqueEnabled(bool );		// range 0 -    1  
		bool setLedStatus(const uint8_t& );			// range 0 -    7  
		bool setDGain(const uint8_t& );				// range 0 -  254 
		bool setIGain(const uint8_t& );				// range 0 -  254 
		bool setPGain(const uint8_t& );				// range 0 -  254 
		bool setGoalPosition(const uint16_t& );		// range 0 - 1023
		bool setGoalSpeed(const uint16_t& );		// range 0 - 2047
		bool setTorqueLimit(const uint16_t& );		// range 0 - 1023
		bool setPunch(const uint16_t& );			// range 0 - 1023
		
		
		
		void createGui();
		
		std::shared_ptr<ServoGui<Model> > gui = nullptr;
		

	protected:
		
		ofEventListener listener;
		
		void onParamChange(dxlEventType& e);
		
		
		int comm_result = COMM_TX_FAIL;
		uint8_t error;
		uint8_t data1Byte;		
		uint16_t data2Byte;
		uint32_t data4Byte;
		uint8_t id;
				
		std::weak_ptr<Connection> connection;
		
		void printResultError(std::string succMsg = "");
		
	};
	typedef Servo<XL320> ServoXL320;

	
}
