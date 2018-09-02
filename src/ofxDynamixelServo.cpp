//
//  ofxDynamixelServo<Model>.cpp
//  example
//
//  Created by Roy Macdonald on 7/23/18.
//
//

#include "ofxDynamixelServo.h"
#include "ofxDynamixelServosModels.h"

namespace ofxDynamixel {
//    template<typename Model>
//	Model Servo<Model>::model = Model();

	
	
	template<typename Model>
	Servo<Model>::Servo(int id, std::shared_ptr<Connection> connection){
		setup(id, connection);
	}
 
    template<typename Model>
    Servo<Model>::Servo(Servo<Model>& mom){
        setup(mom.id, mom.getConnection());
    }
    template<typename Model>
    
    Servo<Model>& Servo<Model>::operator=(Servo<Model>& mom){
        setup(mom.id, mom.getConnection());
    }
    
    
    template<typename Model>
    void Servo<Model>::setup(int id,  std::shared_ptr<Connection> connection){

//		this->model = model;
		this->id = id;
		setConnection(connection);
		
		listener = model.paramChangeEvent.newListener(this,  &Servo<Model>::onParamChange);
		
		
    }
    
	template<typename Model>
	void Servo<Model>::onParamChange(dxlEventType& e){
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
		if(e.length == 1){
			writeData1B(e.address, e.data);
		}else if(e.length == 2){
			writeData2B(e.address, e.data);
		}else if(e.length == 4){
			writeData4B(e.address, e.data);
		}else{
			std::cout << "void Servo<Model>::onParamChange(dxlEventType& e):: cant send data over 4 bytes length!" << std::endl; 
		}
	}
	
	
	template<typename Model>
	void Servo<Model>::updatePresentPosition(){
		readDataTo(model.presentPosition);
	}
    template<typename Model>
    uint8_t Servo<Model>::getId(){
        return this->id;
    }
    
	template<typename Model>
	void Servo<Model>::createGui(){
//		std::cout << __PRETTY_FUNCTION__ << std::endl;
		gui = std::make_shared<ServoGui<Model> >(this->shared_from_this(), getConnection());
	}

    
    template<typename Model>
    std::shared_ptr<Connection> Servo<Model>::getConnection(){
        if(!connection.expired()){
            return connection.lock();
        }
        return nullptr;
    }
    template<typename Model>
    void Servo<Model>::setConnection(std::shared_ptr<Connection> connection){
        this->connection = connection;
    }
    
    template<typename Model>
    bool Servo<Model>::ping()
    {
        auto c = getConnection();
        if(c){
            return c->ping(id);
        }
        return false;
    }
    
    template<typename Model>
    bool Servo<Model>::reset(ResetOption option)
    {
        auto c = getConnection();
        if(c){
            return c->reset(id, option);
        }
        return false;
    }
    
    template<typename Model>
    bool Servo<Model>::initialize(){
        auto c = getConnection();
        if(c){
            return c->clearPort();
        }
        return false;    
    }
    
    
    template<typename Model>
    void Servo<Model>::stop(){
        auto c = getConnection();
        if(c){
            return c->closePort();
        }
    }
    
    template<typename Model>
    void Servo<Model>::printResultError(std::string succMsg) {
        auto c = getConnection();
        if(c){
            
            if (comm_result != COMM_SUCCESS) {
                printf("%s\n", c->getPacketHandler()->getTxRxResult(comm_result));
            } else if (error != 0) {
                printf("%s\n", c->getPacketHandler()->getRxPacketError(error));
            } else if (!succMsg.empty()) {
                std::cout << succMsg << std::endl;
            }
        }
    }
	template<typename Model>
	int Servo<Model>::readData1B(uint16_t address) {
		auto c = getConnection();
		if(c){
			comm_result = c->getPacketHandler()->read1ByteTxRx(c->getPortHandler().get(), id, address, &data1Byte, &error);
			if(comm_result == COMM_SUCCESS){
				return data1Byte;
			}
		}
		return -1;
	}
    
    template<typename Model>
    int Servo<Model>::readData2B(uint16_t address) {
        auto c = getConnection();
        if(c){
            comm_result = c->getPacketHandler()->read2ByteTxRx(c->getPortHandler().get(), id, address, &data2Byte, &error);
			if(comm_result == COMM_SUCCESS){
				return data2Byte;
			}
		}
		return -1;
    }

	template<typename Model>
	int Servo<Model>::readData4B(uint16_t address) {
		auto c = getConnection();
		if(c){
			comm_result = c->getPacketHandler()->read4ByteTxRx(c->getPortHandler().get(), id, address, &data4Byte, &error);
			if(comm_result == COMM_SUCCESS){
				return data4Byte;
			}
		}
		return -1;
	}

	template<typename Model>
	int Servo<Model>::writeData1B(int address, uint8_t dataChange) {            
	//	std::cout << __PRETTY_FUNCTION__ << std::endl;
		auto c = getConnection();
		if(c){
			return c->getPacketHandler()->write1ByteTxRx(c->getPortHandler().get(), id, address, (uint8_t)dataChange, &error);
		}
//		 printResultError(); 
		return -1;
	}
    template<typename Model>
    int Servo<Model>::writeData2B(int address, uint16_t dataChange) {
	//	std::cout << __PRETTY_FUNCTION__ << std::endl;
        auto c = getConnection();
        if(c){
                return c->getPacketHandler()->write2ByteTxRx(c->getPortHandler().get(), id, address, (uint16_t)dataChange, &error);
        }
//         printResultError(); 
        return -1;
    }
	template<typename Model>
	int Servo<Model>::writeData4B(int address, uint32_t dataChange) {            
	//	std::cout << __PRETTY_FUNCTION__ << std::endl;
		auto c = getConnection();
		if(c){
			
			return c->getPacketHandler()->write4ByteTxRx(c->getPortHandler().get(), id, address, dataChange, &error);
		}
//		 printResultError(); 
		return -1;
	}

	
	template<typename Model>
	void Servo<Model>::updateAllParamsFromServo(){
		for(auto t: model.table){
			readDataTo(t, true);
		}
	}
	
    template<typename Model> uint16_t Servo<Model>::getModelNumber(){         this->readDataTo(model.modelNumber);          return model.modelNumber.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getFirmwareVersion(){     this->readDataTo(model.firmwareVersion);      return model.firmwareVersion.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getIdFromServo(){         this->readDataTo(model.id);                    return model.id.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getBaudRate(){            this->readDataTo(model.baudRate);             return model.baudRate.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getReturnDelayTime(){     this->readDataTo(model.returnDelayTime);     return model.returnDelayTime.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getTemperatureLimit(){    this->readDataTo(model.temperatureLimit);     return model.temperatureLimit.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getMinVoltageLimit(){     this->readDataTo(model.minVoltageLimit);     return model.minVoltageLimit.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getMaxVoltageLimit(){     this->readDataTo(model.maxVoltageLimit);     return model.maxVoltageLimit.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getStatusReturnLevel(){   this->readDataTo(model.statusReturnLevel);   return model.statusReturnLevel.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getShutdown(){            this->readDataTo(model.shutdown);              return model.shutdown.R_value; }
    template<typename Model> bool     Servo<Model>::getTorqueEnabled(){       this->readDataTo(model.torqueEnabled);         return model.torqueEnabled.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getLedStatus(){           this->readDataTo(model.led);                   return model.led.R_value; }
    template<typename Model> uint16_t Servo<Model>::getGoalPosition(){        this->readDataTo(model.goalPosition);         return model.goalPosition.R_value; }
    template<typename Model> uint16_t Servo<Model>::getPresentPosition(){     this->readDataTo(model.presentPosition);      return model.presentPosition.R_value; }
    template<typename Model> uint16_t Servo<Model>::getPresentLoad(){         this->readDataTo(model.presentLoad);          return model.presentLoad.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getPresentTemperature(){  this->readDataTo(model.presentTemperature);   return model.presentTemperature.R_value; }
    template<typename Model> uint8_t  Servo<Model>::getMoving(){              this->readDataTo(model.moving);                return model.moving.R_value; }
//    template<typename Model> uint16_t Servo<Model>::getCwAngleLimit(){        this->readDataTo(model.cwAngleLimit);        return model.cwAngleLimit.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getCcwAngleLimit(){       this->readDataTo(model.ccwAngleLimit);       return model.ccwAngleLimit.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getControlMode(){         this->readDataTo(model.controlMode);          return model.controlMode.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getMaxTorque(){           this->readDataTo(model.maxTorque);            return model.maxTorque.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getDGain(){               this->readDataTo(model.dGain);                return model.dGain.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getIGain(){               this->readDataTo(model.iGain);                return model.iGain.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getPGain(){               this->readDataTo(model.pGain);                return model.pGain.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getGoalSpeed(){           this->readDataTo(model.goalSpeed);          return model.goalSpeed.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getTorqueLimit(){         this->readDataTo(model.torqueLimit);          return model.torqueLimit.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getPunch(){               this->readDataTo(model.punch);                 return model.punch.R_values; }
//    template<typename Model> uint16_t Servo<Model>::getPresentSpeed(){        this->readDataTo(model.presentSpeed);         return model.presentSpeed.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getPresentVoltage(){      this->readDataTo(model.presentVoltage);       return model.presentVoltage.R_values; }
//    template<typename Model> uint8_t  Servo<Model>::getRegistered(){          this->readDataTo(model.registered);            return model.registered.R_values; }
    template<typename Model> uint8_t  Servo<Model>::getHardwareErrorStatus(){ this->readDataTo(model.hardwareErrorStatus); return model.hardwareErrorStatus.R_value; }


    template<typename Model> void Servo<Model>::setId(                     uint8_t   value){ model.id.W_value = value;}
    template<typename Model> void Servo<Model>::setBaudRate(const          uint8_t&  value){ model.baudRate.W_value = value;}
    template<typename Model> void Servo<Model>::setReturnDelayTime(const   uint8_t&  value){ model.returnDelayTime.W_value = value;}
    template<typename Model> void Servo<Model>::setTemperatureLimit(const  uint8_t&  value){ model.temperatureLimit.W_value = value;}
    template<typename Model> void Servo<Model>::setMinVoltageLimit(const   uint8_t&  value){ model.minVoltageLimit.W_value = value;}
    template<typename Model> void Servo<Model>::setMaxVoltageLimit(const   uint8_t&  value){ model.maxVoltageLimit.W_value = value;}
    template<typename Model> void Servo<Model>::setGoalPosition(const      uint16_t& value){ model.goalPosition.W_value = value;}
    template<typename Model> void Servo<Model>::setStatusReturnLevel(const uint8_t&  value){ model.statusReturnLevel.W_value = value;}
    template<typename Model> void Servo<Model>::setShutdown(const          uint8_t&  value){ model.shutdown.W_value = value;}
    template<typename Model> void Servo<Model>::setTorqueEnabled(          bool      value){ model.torqueEnabled.W_value = value;}
    template<typename Model> void Servo<Model>::setLedStatus(const         uint8_t&  value){ model.led.W_value = value;}
//    template<typename Model> void  Servo<Model>::setMaxTorque(const         uint16_t& value){ model.maxTorque = value;}
//    template<typename Model> void  Servo<Model>::setCwAngleLimit(const      uint16_t& value){ model.cwAngleLimit = value;}
//    template<typename Model> void  Servo<Model>::setCcwAngleLimit(const     uint16_t& value){ model.ccwAngleLimit = value;}
//    template<typename Model> void  Servo<Model>::setControlMode(const       uint8_t&  value){ model.controlMode = value;}
//    template<typename Model> void  Servo<Model>::setDGain(const             uint8_t&  value){ model.dGain = value;}
//    template<typename Model> void  Servo<Model>::setIGain(const             uint8_t&  value){ model.iGain = value;}
//    template<typename Model> void  Servo<Model>::setPGain(const             uint8_t&  value){ model.pGain = value;}
//    template<typename Model> void  Servo<Model>::setGoalSpeed(const         uint16_t& value){ model.goalSpeed = value;}
//    template<typename Model> void  Servo<Model>::setTorqueLimit(const       uint16_t& value){ model.torqueLimit = value;}
//    template<typename Model> void  Servo<Model>::setPunch(const             uint16_t& value){ model.punch = value;}

	
	

	
//	template class Servo<AX12>;
	template class Servo<XL320>;
	template class Servo<XL430>;
	
	
	
}
