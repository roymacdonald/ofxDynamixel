//
//  ofxDynamixelBaseServo<Model>.cpp
//  example
//
//  Created by Roy Macdonald on 7/23/18.
//
//

#include "ofxDynamixelBaseServo.h"


namespace ofxDynamixel {
    
    template<typename Model>
    BaseServo<Model>::BaseServo(BaseServo<Model>& mom){
        setup(mom.id, mom.getConnection());
    }
    template<typename Model>
    
    BaseServo<Model>& BaseServo<Model>::operator=(BaseServo<Model>& mom){
        setup(mom.id, mom.getConnection());
    }
    
    
    template<typename Model>
    void BaseServo<Model>::setup(int id, std::shared_ptr<Connection> connection){
        setConnection(connection);
    }
    
    template<typename Model>
    uint8_t BaseServo<Model>::getId(){
        return this->id;
    }
    
    
    template<typename Model>
    std::shared_ptr<Connection> BaseServo<Model>::getConnection(){
        if(!connection.expired()){
            return connection.lock();
        }
        return nullptr;
    }
    template<typename Model>
    void BaseServo<Model>::setConnection(std::shared_ptr<Connection> connection){
        this->connection = connection;
    }
    
    template<typename Model>
    bool BaseServo<Model>::ping()
    {
        auto c = getConnection();
        if(c){
            return c->ping(id);
        }
        return false;
    }
    
    template<typename Model>
    bool BaseServo<Model>::reset(ResetOption option)
    {
        auto c = getConnection();
        if(c){
            return c->reset(id, option);
        }
        return false;
    }
    
    template<typename Model>
    bool BaseServo<Model>::initialize(){
        auto c = getConnection();
        if(c){
            return c->clearPort();
        }
        return false;    
    }
    
    
    template<typename Model>
    void BaseServo<Model>::stop(){
        auto c = getConnection();
        if(c){
            return c->closePort();
        }
    }
    
    template<typename Model>
    void BaseServo<Model>::printResultError(std::string succMsg) {
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
    void BaseServo<Model>::readData2B(uint16_t address) {
        auto c = getConnection();
        if(c){
           c->getPacketHandler()->read2ByteTxRx(c->getPortHandler().get(), id, address, &data2Byte, &error);
        }
    }

    template<typename Model>
    void BaseServo<Model>::readData1B(uint16_t address) {
        auto c = getConnection();
        if(c){
            c->getPacketHandler()->read1ByteTxRx(c->getPortHandler().get(), id, address, &data1Byte, &error);
        }
    }

    
    template<typename Model>
    int BaseServo<Model>::writeData2B(int address, int dataChange) {
        auto c = getConnection();
        if(c){
                return c->getPacketHandler()->write2ByteTxRx(c->getPortHandler().get(), id, address, (uint16_t)dataChange, &error);
        }
        // printResultError(); 
        return -1;
    }
    template<typename Model>
    int BaseServo<Model>::writeData1B(int address, int dataChange) {            
        auto c = getConnection();
        if(c){
                return c->getPacketHandler()->write1ByteTxRx(c->getPortHandler().get(), id, address, (uint8_t)dataChange, &error);
         }
         // printResultError(); 
         return -1;
    }
    
    template<typename Model> uint16_t BaseServo<Model>::getModelNumber(){         this->readData2B(Model::MODEL_NUMBER());          return data2Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getFirmwareVersion(){     this->readData1B(Model::FIRMWARE_VERSION());      return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getIdFromServo(){         this->readData1B(Model::ID());                    return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getBaudRate(){            this->readData1B(Model::BAUD_RATE());             return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getReturnDelayTime(){     this->readData1B(Model::RETURN_DELAY_TIME());     return data1Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getCwAngleLimit(){        this->readData2B(Model::CW_ANGLE_LIMIT());        return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getCcwAngleLimit(){       this->readData2B(Model::CCW_ANGLE_LIMIT());       return data2Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getControlMode(){         this->readData1B(Model::CONTROL_MODE());          return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getTemperatureLimit(){    this->readData1B(Model::TEMPERATURE_LIMIT());     return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getMinVoltageLimit(){     this->readData1B(Model::MIN_VOLTAGE_LIMIT());     return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getMaxVoltageLimit(){     this->readData1B(Model::MAX_VOLTAGE_LIMIT());     return data1Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getMaxTorque(){           this->readData2B(Model::MAX_TORQUE());            return data2Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getStatusReturnLevel(){   this->readData1B(Model::STATUS_RETURN_LEVEL());   return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getShutdown(){            this->readData1B(Model::SHUTDOWN());              return data1Byte; }
    template<typename Model> bool     BaseServo<Model>::getTorqueEnabled(){       this->readData1B(Model::TORQUE_ENABLE());         return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getLedStatus(){           this->readData1B(Model::LED());                   return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getDGain(){               this->readData1B(Model::D_GAIN());                return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getIGain(){               this->readData1B(Model::I_GAIN());                return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getPGain(){               this->readData1B(Model::P_GAIN());                return data1Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getGoalPosition(){        this->readData2B(Model::GOAL_POSITION());         return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getGoalSpeed(){           this->readData2B(Model::MOVING_SPEED());          return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getTorqueLimit(){         this->readData2B(Model::TORQUE_LIMIT());          return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getPunch(){               this->readData2B(Model::PUNCH());                 return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getPresentPosition(){     this->readData2B(Model::PRESENT_POSITION());      return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getPresentSpeed(){        this->readData2B(Model::PRESENT_SPEED());         return data2Byte; }
    template<typename Model> uint16_t BaseServo<Model>::getPresentLoad(){         this->readData2B(Model::PRESENT_LOAD());          return data2Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getPresentVoltage(){      this->readData1B(Model::PRESENT_VOLTAGE());       return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getPresentTemperature(){  this->readData1B(Model::PRESENT_TEMPERATURE());   return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getRegistered(){          this->readData1B(Model::REGISTERED());            return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getMoving(){              this->readData1B(Model::MOVING());                return data1Byte; }
    template<typename Model> uint8_t  BaseServo<Model>::getHardwareErrorStatus(){ this->readData1B(Model::HARDWARE_ERROR_STATUS()); return data1Byte; }


    template<typename Model> bool BaseServo<Model>::setId(              uint8_t  value){ return this->writeData1B(Model::ID(),                  value);}
    template<typename Model> bool BaseServo<Model>::setBaudRate(const          uint8_t&  value){ return this->writeData1B(Model::BAUD_RATE(),           value);}
    template<typename Model> bool BaseServo<Model>::setReturnDelayTime(const   uint8_t&  value){ return this->writeData1B(Model::RETURN_DELAY_TIME(),   value);}
    template<typename Model> bool BaseServo<Model>::setCwAngleLimit(const      uint16_t& value){ return this->writeData2B(Model::CW_ANGLE_LIMIT(),      value);}
    template<typename Model> bool BaseServo<Model>::setCcwAngleLimit(const     uint16_t& value){ return this->writeData2B(Model::CCW_ANGLE_LIMIT(),     value);}
    template<typename Model> bool BaseServo<Model>::setControlMode(const       uint8_t&  value){ return this->writeData1B(Model::CONTROL_MODE(),        value);}
    template<typename Model> bool BaseServo<Model>::setTemperatureLimit(const  uint8_t&  value){ return this->writeData1B(Model::TEMPERATURE_LIMIT(),   value);}
    template<typename Model> bool BaseServo<Model>::setMinVoltageLimit(const   uint8_t&  value){ return this->writeData1B(Model::MIN_VOLTAGE_LIMIT(),   value);}
    template<typename Model> bool BaseServo<Model>::setMaxVoltageLimit(const   uint8_t&  value){ return this->writeData1B(Model::MAX_VOLTAGE_LIMIT(),   value);}
    template<typename Model> bool BaseServo<Model>::setMaxTorque(const         uint16_t& value){ return this->writeData2B(Model::MAX_TORQUE(),          value);}
    template<typename Model> bool BaseServo<Model>::setStatusReturnLevel(const uint8_t&  value){ return this->writeData1B(Model::STATUS_RETURN_LEVEL(), value);}
    template<typename Model> bool BaseServo<Model>::setShutdown(const          uint8_t&  value){ return this->writeData1B(Model::SHUTDOWN(),            value);}
    template<typename Model> bool BaseServo<Model>::setTorqueEnabled(          bool      value){ return this->writeData1B(Model::TORQUE_ENABLE(),       value);}
    template<typename Model> bool BaseServo<Model>::setLedStatus(const         uint8_t&  value){ return this->writeData1B(Model::LED(),                 value);}
    template<typename Model> bool BaseServo<Model>::setDGain(const             uint8_t&  value){ return this->writeData1B(Model::D_GAIN(),              value);}
    template<typename Model> bool BaseServo<Model>::setIGain(const             uint8_t&  value){ return this->writeData1B(Model::I_GAIN(),              value);}
    template<typename Model> bool BaseServo<Model>::setPGain(const             uint8_t&  value){ return this->writeData1B(Model::P_GAIN(),              value);}
    template<typename Model> bool BaseServo<Model>::setGoalPosition(const      uint16_t& value){ return this->writeData2B(Model::GOAL_POSITION(),       value);}
    template<typename Model> bool BaseServo<Model>::setGoalSpeed(const         uint16_t& value){ return this->writeData2B(Model::MOVING_SPEED(),        value);}
    template<typename Model> bool BaseServo<Model>::setTorqueLimit(const       uint16_t& value){ return this->writeData2B(Model::TORQUE_LIMIT(),        value);}
    template<typename Model> bool BaseServo<Model>::setPunch(const             uint16_t& value){ return this->writeData2B(Model::PUNCH(),               value);}
	
	
	template class BaseServo<AX12>;
	template class BaseServo<XL320>;
}
