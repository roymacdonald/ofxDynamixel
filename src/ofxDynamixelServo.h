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
		uint32_t tempPos;
		
		Servo(){
			uniqueID = makeUniqueID();
//			std::cout << "Servo(): " << (int)uniqueID << "  " << model.getModelName() <<"\n";
		}
		Servo(int id, std::shared_ptr<Connection> connection);
		
		virtual ~Servo(){}
		Servo(Servo&);
		Servo& operator=(Servo&);
		
		virtual void setup(int id, std::shared_ptr<Connection> connection);

		std::shared_ptr<Connection> getConnection();
		void setConnection(std::shared_ptr<Connection> connection);
		
		
		void stepBy(int numSteps, unsigned short pGain);
		void restorePreviousPGain();
		
		bool ping();		
		bool reset(ResetOption option = RESET_ALL_BUT_ID_AND_BAUD);
		bool initialize();		
		void stop();
		bool reboot();
		
		//void moveWithAcceleration(int goalPosition, int movingSpeed, int accelerationSpeed);
		
		ofEvent<void> movementEndEvent; 
		
		
		

		template<typename ValType>
		int writeDataFrom(dxlParameter<ValType>* param){
			if(!param){
				std::cout << "writeDataFrom(dxlParameter<ValType>* param)   nullptr param! " << std::endl;
				return -1;
			}
			if(param->getLength() != 1 && param->getLength() != 2 && param->getLength() != 4){
				std::cout << "writeDataFrom(dxlParameter<ValType>* param)   invalid param getLength() " << (int) param->getLength() << std::endl;
				return -1;
			}
			auto c = getConnection();
			if(c){
				std::vector<uint8_t> data_write;//(param->getLength(), 0);
				ValType data = param->W_value.get();
				if(param->getLength() == 1){
    				data_write[0] = data;
				}else if(param->getLength() == 2){
					data_write = { DXL_LOBYTE(data), DXL_HIBYTE(data) };
				}else if(param->getLength() == 4){
					data_write = { DXL_LOBYTE(DXL_LOWORD(data)), DXL_HIBYTE(DXL_LOWORD(data)), DXL_LOBYTE(DXL_HIWORD(data)), DXL_HIBYTE(DXL_HIWORD(data)) };
				}	
				comm_result = c->getPacketHandler()->writeTxRx(c->getPortHandler().get(), id, param->address, data_write.size(), data_write.data(), &error);
				 printResultError(); 
				return comm_result;
			}
		}
		template<typename ValType>
		int writeDataFrom(dxlParameter<ValType>& param){
			return writeDataFrom(&param); 
		}
		int writeDataFrom(baseDxlParameter* param){
			if(param->getLength() == 1){
				return writeDataFrom(dynamic_cast<dxlParameter<uint8_t>* >(param));
			}else if(param->getLength() == 2){
				return writeDataFrom(dynamic_cast<dxlParameter<uint16_t>* >(param));
			}else if(param->getLength() == 4){
				return writeDataFrom(dynamic_cast<dxlParameter<uint32_t>* >(param));
			}
		}
		
		
		template<typename ValType>
		int readDataTo(dxlParameter<ValType>* param, bool bUpdateWriteParam = false){
			if(!param){
				std::cout << typeid(model).name() << "  " << typeid(ValType).name() <<  " readDataTo(dxlParameter<"<< typeid(ValType).name() << ">* param)   nullptr param!   bUpdateWriteParam: " << (std::string)(bUpdateWriteParam?"TRUE":"FALSE") ;//<< std::endl;
				return-1;
			}
			if(param->getLength() != 1 && param->getLength() != 2 && param->getLength() != 4){
				std::cout << "readDataTo(dxlParameter<ValType>* param)   invalid param getLength() " << (int) param->getLength() << std::endl;
				return -1;
			}
			auto c = getConnection();
			if(c){
//				 = c->getPacketHandler()->read4ByteTxRx(c->getPortHandler().get(), id, address, &data4Byte, &error);

				std::vector<uint8_t> data_read(param->getLength(), 0);
				comm_result = c->getPacketHandler()->readTxRx(c->getPortHandler().get(), id, param->address, data_read.size(), data_read.data(), &error);
				if (comm_result == COMM_SUCCESS){
					if(param->getLength() == 1){
    					param->R_value = data_read[0];
					}else if(param->getLength() == 2){
				    	param->R_value  = DXL_MAKEWORD(data_read[0], data_read[1]);
					}else if(param->getLength() == 4){
						param->R_value = DXL_MAKEDWORD(DXL_MAKEWORD(data_read[0], data_read[1]), DXL_MAKEWORD(data_read[2], data_read[3]));
					}
					if(!param->bReadOnly && bUpdateWriteParam){
						param->W_value.setWithoutEventNotifications(param->R_value.get());
					
					}
					
					
				}
				//return comm_result;

//				if(comm_result == COMM_SUCCESS){
//					return data4Byte;
//				}
			}
			return comm_result;
		}
		template<typename ValType>
		int readDataTo(dxlParameter<ValType>& param, bool bUpdateWriteParam = false){
			return readDataTo(&param, bUpdateWriteParam);
		}
		
		int readDataTo(baseDxlParameter* param,  bool bUpdateWriteParam = false){
			int ret = -1;
			if(param->getType() == "h"){
				ret = readDataTo(dynamic_cast<dxlParameter<uint8_t>* >(param), bUpdateWriteParam);
//				if(ret == -1){
//					std::cout << param->name << "\n";
//				}
			}else if(param->getType() == "b"){
				ret = readDataTo(dynamic_cast<dxlParameter<bool>* >(param), bUpdateWriteParam);
			}else if(param->getType() == "t"){
				ret = readDataTo(dynamic_cast<dxlParameter<uint16_t>* >(param), bUpdateWriteParam);
			}else if(param->getType() == "j"){
				ret = readDataTo(dynamic_cast<dxlParameter<uint32_t>* >(param), bUpdateWriteParam);
			}
			
			return ret;
		}
		
		
		int readData1B(uint16_t address);
		int readData2B(uint16_t address);
		int readData4B(uint16_t address);
		int writeData1B(int address, uint8_t dataChange);
		int writeData2B(int address, uint16_t dataChange);
		int writeData4B(int address, uint32_t dataChange);
		
		void updatePresentPosition();
		void updateAllParamsFromServo();
		
		static size_t makeUniqueID();
		uint16_t   getModelNumber();         // Model Number                        R
		uint8_t    getFirmwareVersion();     // Firmware Version                    R
		uint8_t    getId();					 // returns the locally stored id
		uint8_t    getIdFromServo();         // DYNAMIXEL ID                        RW  0 - 252
		uint8_t    getBaudRate();            // Communication Speed                 RW  0 -  3
		uint8_t    getReturnDelayTime();     // Response Delay Time                 RW  0 - 254
		// uint16_t   getCwAngleLimit();        // Clockwise Angle Limit               RW  0 - 1023
		// uint16_t   getCcwAngleLimit();       // Counter_Clockwise Angle Limit       RW  0 - 1023
		// uint8_t    getControlMode();         // Control Mode                        RW  1 -  2
		uint8_t    getTemperatureLimit();    // Maximum Internal Temperature Limit  RW  0 - 150
		uint8_t    getMinVoltageLimit();     // Minimum Input Voltage Limit         RW  50 - 250
		uint8_t    getMaxVoltageLimit();     // Maximum Input Voltage Limit         RW  50 - 250
		// uint16_t   getMaxTorque();           // Maximun Torque                      RW  0 - 1023
		uint8_t    getStatusReturnLevel();   // Select Types of Status Return       RW  0 -  2
		uint8_t    getShutdown();            // Shutdown Error Information          RW  0 -  7
		 bool       getTorqueEnabled();       // Motor Torque On/Off                 RW   0 -  1
		uint8_t    getLedStatus();           // Status LED On/Off                   RW   0 -  7
		// uint8_t    getDGain();               // Derivative Gain                     RW   0 - 254
		// uint8_t    getIGain();               // Integral Gain                       RW   0 - 254
		// uint8_t    getPGain();               // Proportional Gain                   RW   0 - 254
		uint16_t   getGoalPosition();        // Desired Position                    RW   0 - 1023
		// uint16_t   getGoalSpeed();           // Moving Speed(Moving Velocity)       RW   0 - 2047
		// uint16_t   getTorqueLimit();         // Torque Limit(Goal Torque)           RW   0 - 1023
		// uint16_t   getPunch();               // Minimum Current Threshold           RW   0 - 1023
		uint16_t   getPresentPosition();     // Present Position                    R
		// uint16_t   getPresentSpeed();        // Present Speed                       R
		uint16_t   getPresentLoad();         // Present Load                        R
		// uint8_t    getPresentVoltage();      // Present Voltage                     R
		uint8_t    getPresentTemperature();  // Present Temperature                 R
		uint8_t    getRegistered();          // If Instruction is registered        R
		uint8_t    getMoving();              // Movement Status                     R
		uint8_t    getHardwareErrorStatus(); // Hardware Error Status               R
		
		
		
		void setId(uint8_t );				// range 0 -  252
		void setBaudRate(const uint8_t& );			// range 0 -    3   
		void setReturnDelayTime(const uint8_t& );	// range 0 -  254  
		// void setCwAngleLimit(const uint16_t& );		// range 0 - 1023 
		// void setCcwAngleLimit(const uint16_t& );	// range 0 - 1023 
		// void setControlMode(const uint8_t& );		// range 1 -    2   
		void setTemperatureLimit(const uint8_t& );	// range 0 -  150  
		void setMinVoltageLimit(const uint8_t& );	// range 50 - 250  
		void setMaxVoltageLimit(const uint8_t& );	// range 50 - 250  
		// void setMaxTorque(const uint16_t& );		// range 0 - 1023 
		void setStatusReturnLevel(const uint8_t& );	// range 0 -    2   
		void setPID(const uint16_t& p, const uint16_t&  i, const uint16_t& d);
		void setShutdown(const uint8_t& );			// range 0 -    7   
		void setTorqueEnabled(bool );		// range 0 -    1  
		void setLedStatus(const uint8_t& );			// range 0 -    7  
		// void setDGain(const uint8_t& );				// range 0 -  254 
		// void setIGain(const uint8_t& );				// range 0 -  254 
		// void setPGain(const uint8_t& );				// range 0 -  254 
		void setGoalPosition(const uint16_t& );		// range 0 - 1023
		// void setGoalSpeed(const uint16_t& );		// range 0 - 2047
		// void setTorqueLimit(const uint16_t& );		// range 0 - 1023
		// void setPunch(const uint16_t& );			// range 0 - 1023
		
		
		
		void createGui(float guiWidth = 350);
		
		std::shared_ptr<ServoGui<Model> > gui = nullptr;
		
		void drawGui();

	protected:
		size_t uniqueID;
		void onPosChange(dxlEventType& e);
		ofEventListener listener;
		
		ofEventListener posChangeListener;
		
		void onParamChange(dxlEventType& e);
		
		
		int comm_result = COMM_TX_FAIL;
		uint8_t error;
		uint8_t data1Byte;		
		uint16_t data2Byte;
		uint32_t data4Byte;
		uint8_t id;
		
		bool bUsingTempPGain = false;
		unsigned short prevPGain;
				
		std::weak_ptr<Connection> connection;
		
		void printResultError(std::string succMsg = "");
	private:
		bool bPresentPositionNeedUpdate = false;
	};
	

	
}
