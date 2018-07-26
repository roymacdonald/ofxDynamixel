//
//  ofxDynamixelServo<Model>.cpp
//  example
//
//  Created by Roy Macdonald on 7/23/18.
//
//

#include "ofxDynamixelServo.h"


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
	void Servo<Model>::readData1B(uint16_t address) {
		auto c = getConnection();
		if(c){
			c->getPacketHandler()->read1ByteTxRx(c->getPortHandler().get(), id, address, &data1Byte, &error);
		}
	}
    
    template<typename Model>
    void Servo<Model>::readData2B(uint16_t address) {
        auto c = getConnection();
        if(c){
           c->getPacketHandler()->read2ByteTxRx(c->getPortHandler().get(), id, address, &data2Byte, &error);
        }
    }

	template<typename Model>
	void Servo<Model>::readData4B(uint16_t address) {
		auto c = getConnection();
		if(c){
			c->getPacketHandler()->read4ByteTxRx(c->getPortHandler().get(), id, address, &data4Byte, &error);
		}
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

	
	
	
    template<typename Model> uint16_t Servo<Model>::getModelNumber(){         this->readData2B(model.modelNumber.address);          return data2Byte; }
    template<typename Model> uint8_t  Servo<Model>::getFirmwareVersion(){     this->readData1B(model.firmwareVersion.address);      return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getIdFromServo(){         this->readData1B(model.id.address);                    return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getBaudRate(){            this->readData1B(model.baudRate.address);             return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getReturnDelayTime(){     this->readData1B(model.returnDelayTime.address);     return data1Byte; }
    template<typename Model> uint16_t Servo<Model>::getCwAngleLimit(){        this->readData2B(model.cwAngleLimit.address);        return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getCcwAngleLimit(){       this->readData2B(model.ccwAngleLimit.address);       return data2Byte; }
    template<typename Model> uint8_t  Servo<Model>::getControlMode(){         this->readData1B(model.controlMode.address);          return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getTemperatureLimit(){    this->readData1B(model.temperatureLimit.address);     return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getMinVoltageLimit(){     this->readData1B(model.minVoltageLimit.address);     return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getMaxVoltageLimit(){     this->readData1B(model.maxVoltageLimit.address);     return data1Byte; }
    template<typename Model> uint16_t Servo<Model>::getMaxTorque(){           this->readData2B(model.maxTorque.address);            return data2Byte; }
    template<typename Model> uint8_t  Servo<Model>::getStatusReturnLevel(){   this->readData1B(model.statusReturnLevel.address);   return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getShutdown(){            this->readData1B(model.shutdown.address);              return data1Byte; }
    template<typename Model> bool     Servo<Model>::getTorqueEnabled(){       this->readData1B(model.torqueEnabled.address);         return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getLedStatus(){           this->readData1B(model.led.address);                   return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getDGain(){               this->readData1B(model.dGain.address);                return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getIGain(){               this->readData1B(model.iGain.address);                return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getPGain(){               this->readData1B(model.pGain.address);                return data1Byte; }
    template<typename Model> uint16_t Servo<Model>::getGoalPosition(){        this->readData2B(model.goalPosition.address);         return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getGoalSpeed(){           this->readData2B(model.goalSpeed.address);          return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getTorqueLimit(){         this->readData2B(model.torqueLimit.address);          return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getPunch(){               this->readData2B(model.punch.address);                 return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getPresentPosition(){     this->readData2B(model.presentPosition.address);      return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getPresentSpeed(){        this->readData2B(model.presentSpeed.address);         return data2Byte; }
    template<typename Model> uint16_t Servo<Model>::getPresentLoad(){         this->readData2B(model.presentLoad.address);          return data2Byte; }
    template<typename Model> uint8_t  Servo<Model>::getPresentVoltage(){      this->readData1B(model.presentVoltage.address);       return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getPresentTemperature(){  this->readData1B(model.presentTemperature.address);   return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getRegistered(){          this->readData1B(model.registered.address);            return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getMoving(){              this->readData1B(model.moving.address);                return data1Byte; }
    template<typename Model> uint8_t  Servo<Model>::getHardwareErrorStatus(){ this->readData1B(model.hardwareErrorStatus.address); return data1Byte; }


    template<typename Model> bool Servo<Model>::setId(                     uint8_t   value){ return this->writeData1B(model.id.address,                  value);}
    template<typename Model> bool Servo<Model>::setBaudRate(const          uint8_t&  value){ return this->writeData1B(model.baudRate.address,           value);}
    template<typename Model> bool Servo<Model>::setReturnDelayTime(const   uint8_t&  value){ return this->writeData1B(model.returnDelayTime.address,   value);}
    template<typename Model> bool Servo<Model>::setCwAngleLimit(const      uint16_t& value){ return this->writeData2B(model.cwAngleLimit.address,      value);}
    template<typename Model> bool Servo<Model>::setCcwAngleLimit(const     uint16_t& value){ return this->writeData2B(model.ccwAngleLimit.address,     value);}
    template<typename Model> bool Servo<Model>::setControlMode(const       uint8_t&  value){ return this->writeData1B(model.controlMode.address,        value);}
    template<typename Model> bool Servo<Model>::setTemperatureLimit(const  uint8_t&  value){ return this->writeData1B(model.temperatureLimit.address,   value);}
    template<typename Model> bool Servo<Model>::setMinVoltageLimit(const   uint8_t&  value){ return this->writeData1B(model.minVoltageLimit.address,   value);}
    template<typename Model> bool Servo<Model>::setMaxVoltageLimit(const   uint8_t&  value){ return this->writeData1B(model.maxVoltageLimit.address,   value);}
    template<typename Model> bool Servo<Model>::setMaxTorque(const         uint16_t& value){ return this->writeData2B(model.maxTorque.address,          value);}
    template<typename Model> bool Servo<Model>::setStatusReturnLevel(const uint8_t&  value){ return this->writeData1B(model.statusReturnLevel.address, value);}
    template<typename Model> bool Servo<Model>::setShutdown(const          uint8_t&  value){ return this->writeData1B(model.shutdown.address,            value);}
    template<typename Model> bool Servo<Model>::setTorqueEnabled(          bool      value){ return this->writeData1B(model.torqueEnabled.address,       value);}
    template<typename Model> bool Servo<Model>::setLedStatus(const         uint8_t&  value){ return this->writeData1B(model.led.address,                 value);}
    template<typename Model> bool Servo<Model>::setDGain(const             uint8_t&  value){ return this->writeData1B(model.dGain.address,              value);}
    template<typename Model> bool Servo<Model>::setIGain(const             uint8_t&  value){ return this->writeData1B(model.iGain.address,              value);}
    template<typename Model> bool Servo<Model>::setPGain(const             uint8_t&  value){ return this->writeData1B(model.pGain.address,              value);}
    template<typename Model> bool Servo<Model>::setGoalPosition(const      uint16_t& value){ return this->writeData2B(model.goalPosition.address,       value);}
    template<typename Model> bool Servo<Model>::setGoalSpeed(const         uint16_t& value){ return this->writeData2B(model.goalSpeed.address,        value);}
    template<typename Model> bool Servo<Model>::setTorqueLimit(const       uint16_t& value){ return this->writeData2B(model.torqueLimit.address,        value);}
    template<typename Model> bool Servo<Model>::setPunch(const             uint16_t& value){ return this->writeData2B(model.punch.address,               value);}

	
	
	
	
//	template class Servo<AX12>;
	template class Servo<XL320>;
	
	
	
}
