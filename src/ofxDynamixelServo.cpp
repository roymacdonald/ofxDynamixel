#include "ofxDynamixelServo.h"
#include "ofxDynamixelControlTables.h"
#include "ofxDynamixelConstants.h"

namespace ofxDynamixel{


#define SET_PARAM_RW(param, group, C, M, X)\
G_##param.setName(#param);\
G_##param.add(W_##param.set("W", C, M, X ));\
grp_##group.add(G_##param);

//R_##param.setName("R");\
//G_##param.add(R_##param);\
//G_##param.add(R_##param.set("R", C,  M, X ));\


#define SET_PARAM_R(param, group)\
R_##param.setName(#param);\
grp_##group.add(R_##param);\



	
//template<typename Model>
//void ServoGui<Model>::setup(){


void printGuiGroup(ofxGuiGroup * group, std::string prefix = ""){
	std::cout << prefix << group->getName() << std::endl;
	for(int i = 0; i < group->getNumControls(); i++){
		auto control = group->getControl(i);
		if(control != nullptr){
			ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
			if(subgroup != nullptr){
				printGuiGroup(subgroup, prefix + "----");
			}else{
				std::cout << prefix + "----"<< control->getName() << std::endl;
			}
		}
	}
}

template<typename Model>
void ServoGui<Model>::setup(int id,  std::shared_ptr<Connection> connection){
	BaseServo<Model>::setup(id, connection);
	parameters.setName("ServoGuiParams");
	grp_eepromParams.setName("EEPROM Params");
	grp_ramParams.setName("RAM Params");
	grp_readParams.setName("Read Params");
		
	SET_PARAM_R(modelNumber, eepromParams );
	SET_PARAM_R(firmwareVersion, eepromParams);
	SET_PARAM_RW(id_param, eepromParams,         1,  0, 252  );
	SET_PARAM_RW(baudRate, eepromParams,             3,  0,  3   );
	SET_PARAM_RW(returnDelayTime, eepromParams,    250,  0, 254  );
	SET_PARAM_RW(cwAngleLimit, eepromParams,         0,  0, 1023 );
	SET_PARAM_RW(ccwAngleLimit, eepromParams,     1023,  0, 1023 );
	SET_PARAM_RW(controlMode, eepromParams,          2,  1,  2   );
	SET_PARAM_RW(temperatureLimit, eepromParams,    65,  0, 150  );
	SET_PARAM_RW(minVoltageLimit, eepromParams,     60, 50, 250  );
	SET_PARAM_RW(maxVoltageLimit, eepromParams,     90, 50, 250  );
	SET_PARAM_RW(maxTorque, eepromParams,         1023,  0, 1023 );
	SET_PARAM_RW(statusReturnLevel, eepromParams,    2,  0,  2   );
	SET_PARAM_RW(shutdown, eepromParams,             3,  0,  7   );
	
	SET_PARAM_RW(torqueEnabled, ramParams,   0, 0, 1  );
	SET_PARAM_RW(ledStatus, ramParams,   0    , 0, 7  );
	SET_PARAM_RW(dGain, ramParams,   0        , 0, 254 );
	SET_PARAM_RW(iGain, ramParams,   0        , 0, 254 );
	SET_PARAM_RW(pGain, ramParams,  32        , 0, 254 );
	SET_PARAM_RW(goalPosition, ramParams,    100 , 0, 1023);
	SET_PARAM_RW(goalSpeed, ramParams,   0   , 0, 2047);
	SET_PARAM_RW(torqueLimit, ramParams,   0  , 0, 1023);
	SET_PARAM_RW(punch, ramParams,  32        , 0, 1023);
	
	
	SET_PARAM_R(presentPosition, readParams);
	SET_PARAM_R(presentSpeed, readParams);
	SET_PARAM_R(presentLoad, readParams);
	SET_PARAM_R(presentVoltage, readParams);
	SET_PARAM_R(presentTemperature, readParams);
	SET_PARAM_R(registered, readParams);
	SET_PARAM_R(moving, readParams);
	SET_PARAM_R(hardwareErrorStatus, readParams);

	
	parameters.add(grp_eepromParams);
	parameters.add(grp_ramParams);
	parameters.add(grp_readParams);

	panel.setup(parameters);
	printGuiGroup(&panel);
	
	setListeners();
}
	template<typename Model>
	void ServoGui<Model>::setListeners(){
		listeners.unsubscribeAll();
		listeners.push(W_id_param.newListener([this](uint8_t&){ this->setId( (uint8_t)W_id_param.get() );}));
	}
	template<typename Model>
	void ServoGui<Model>::update(){
#ifdef ENABLE_GUI_UPDATE
		auto c = this->getConnection();
		if(c){
			c->clearBulkRead();
			c->addBulkReadParam(this->id , Model::MODEL_NUMBER()          , 2);
			c->addBulkReadParam(this->id , Model::FIRMWARE_VERSION()      , 1);
			c->addBulkReadParam(this->id , Model::ID()                    , 1);
			c->addBulkReadParam(this->id , Model::BAUD_RATE()             , 1);
			c->addBulkReadParam(this->id , Model::RETURN_DELAY_TIME()     , 1);
			c->addBulkReadParam(this->id , Model::CW_ANGLE_LIMIT()        , 2);
			c->addBulkReadParam(this->id , Model::CCW_ANGLE_LIMIT()       , 2);
			
			c->addBulkReadParam(this->id, Model::CONTROL_MODE(), 1);
			c->addBulkReadParam(this->id, Model::TEMPERATURE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MIN_VOLTAGE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MAX_VOLTAGE_LIMIT(), 1);
			c->addBulkReadParam(this->id, Model::MAX_TORQUE(), 2);
			c->addBulkReadParam(this->id, Model::STATUS_RETURN_LEVEL(), 1);
			c->addBulkReadParam(this->id, Model::SHUTDOWN(), 1);
			c->addBulkReadParam(this->id, Model::TORQUE_ENABLE(), 1);
			c->addBulkReadParam(this->id, Model::LED(), 1);
			c->addBulkReadParam(this->id, Model::D_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::I_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::P_GAIN(), 1);
			c->addBulkReadParam(this->id, Model::GOAL_POSITION(), 2);
			c->addBulkReadParam(this->id, Model::MOVING_SPEED(), 2);
			c->addBulkReadParam(this->id, Model::TORQUE_LIMIT(), 2);
			c->addBulkReadParam(this->id, Model::PUNCH(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_POSITION(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_SPEED(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_LOAD(), 2);
			c->addBulkReadParam(this->id, Model::PRESENT_VOLTAGE(), 1);
			c->addBulkReadParam(this->id, Model::PRESENT_TEMPERATURE(), 1);
			c->addBulkReadParam(this->id, Model::REGISTERED(), 1);
			c->addBulkReadParam(this->id, Model::MOVING(), 1);
			c->addBulkReadParam(this->id, Model::HARDWARE_ERROR_STATUS(), 1);

			c->bulkReadRequest();// esto debiera estar en otro thread!
			
//			uint8_t  data1
			uint16_t data;
			
			
			if(c->getBulkReadData(this->id , Model::MODEL_NUMBER()          , 2 , data)){  R_modelNumber = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::FIRMWARE_VERSION()      , 1 , data)){  R_firmwareVersion = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::BAUD_RATE()             , 1 , data)){  G_baudRate.setName("baudRate: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::RETURN_DELAY_TIME()     , 1 , data)){  G_returnDelayTime.setName("returnDelayTime: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CW_ANGLE_LIMIT()        , 2 , data)){  G_cwAngleLimit.setName("cwAngleLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CCW_ANGLE_LIMIT()       , 2 , data)){  G_ccwAngleLimit.setName("ccwAngleLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::CONTROL_MODE()          , 1 , data)){  G_controlMode.setName("controlMode: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TEMPERATURE_LIMIT()     , 1 , data)){  G_temperatureLimit.setName("temperatureLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MIN_VOLTAGE_LIMIT()     , 1 , data)){  G_minVoltageLimit.setName("minVoltageLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MAX_VOLTAGE_LIMIT()     , 1 , data)){  G_maxVoltageLimit.setName("maxVoltageLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MAX_TORQUE()            , 2 , data)){  G_maxTorque.setName("maxTorque: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::STATUS_RETURN_LEVEL()   , 1 , data)){  G_statusReturnLevel.setName("statusReturnLevel: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::SHUTDOWN()              , 1 , data)){  G_shutdown.setName("shutdown: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TORQUE_ENABLE()         , 1 , data)){  G_torqueEnabled.setName("torqueEnabled: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::LED()                   , 1 , data)){  G_ledStatus.setName("ledStatus: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::D_GAIN()                , 1 , data)){  G_dGain.setName("dGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::I_GAIN()                , 1 , data)){  G_iGain.setName("iGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::P_GAIN()                , 1 , data)){  G_pGain.setName("pGain: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::GOAL_POSITION()         , 2 , data)){  G_goalPosition.setName("goalPosition: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::MOVING_SPEED()          , 2 , data)){  G_goalSpeed.setName("goalSpeed: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::TORQUE_LIMIT()          , 2 , data)){  G_torqueLimit.setName("torqueLimit: "+  ofToString(data));}
			if(c->getBulkReadData(this->id , Model::PUNCH()                 , 2 , data)){  G_punch.setName("punch: "+  ofToString(data));}		
			if(c->getBulkReadData(this->id , Model::PRESENT_POSITION()      , 2 , data)){  R_presentPosition = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_SPEED()         , 2 , data)){  R_presentSpeed = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_LOAD()          , 2 , data)){  R_presentLoad = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_VOLTAGE()       , 1 , data)){  R_presentVoltage = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::PRESENT_TEMPERATURE()   , 1 , data)){  R_presentTemperature = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::REGISTERED()            , 1 , data)){  R_registered = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::MOVING()                , 1 , data)){  R_moving = ofToString(data);}
			if(c->getBulkReadData(this->id , Model::HARDWARE_ERROR_STATUS() , 1 , data)){  R_hardwareErrorStatus = ofToString(data);}
#endif
		}
		
	
	
	
	
//ofxGuiGroup * findGuiGroup(ofxGuiGroup * group, std::string name){
//	for(int i = 0; i < group->getNumControls(); i++){
//		auto control = group->getControl(i);
//		if(control != nullptr){
//			ofxGuiGroup * subgroup = dynamic_cast <ofxGuiGroup *>(control);
//			if(subgroup != nullptr){
//				if(subgroup->getName() == name){
//					return subgroup;
//				}else{
//					return findGuiGroup(subgroup, name);
//				}
//			}
//		}
//	}
//	return nullptr;
//}

//void ServoGui::disableMouseInput(std::string groupName, std::string paramName){
//
//
//	auto g = findGuiGroup(&panel, groupName);
//	if(g != nullptr){
//		for(int i = 0; i < g->getNumControls(); i++){
//			auto c = g->getControl(i);
//			if(c != nullptr){
//				if(c->getName() == paramName){
//					std::cout << "unregister mouse " << paramName << std::endl;
//					c->unregisterMouseEvents();
//				}
//			}else{
//				std::cout << "Null control " << std::endl;
//			}
//		}
//	}else{
//		std::cout << "No guiGroup " << groupName << std::endl;
//	}
//}
/*
 #define SERVO_MODEL XL320
 //#define SERVO_MODEL AX12
 Servo::Servo(Servo& mom){
	setup(mom.id, mom.getConnection());
	listeners.unsubscribeAll();
	position = mom.position.get();
	speed = mom.speed.get();
	setListeners();	
	positionMinimum = mom.positionMinimum;
	positionMaximum = mom.positionMaximum;
	turnsCount = mom.turnsCount;
 }
 Servo& Servo::operator=(Servo& mom){
	setup(mom.id, mom.getConnection());
	listeners.unsubscribeAll();
	position = mom.position.get();
	speed = mom.speed.get();
	setListeners();	
	positionMinimum = mom.positionMinimum;
	positionMaximum = mom.positionMaximum;
	turnsCount = mom.turnsCount;
 }
 
 
 void Servo::setup(int id, std::shared_ptr<Connection> connection){
	parameters.setName("Servo" + ofToString(id));
	parameters.add(this->id.set("ID", id, 1, 254));
	parameters.add(position.set("position", 0, 0, 1024));
	parameters.add(currentPos.set("currentPos", 0,0,1024)); 
	parameters.add(speed.set("speed", 1000, 0, 2048));
	parameters.add(currentSpeed.set("currentSpeed", 0,0, 2048));
	setConnection(connection);
	setListeners();
 }
 void Servo::setListeners(){
	listeners.unsubscribeAll();
	listeners.push(position.newListener([&](int&){
 setGoalPosition(position.get());
	}));
	listeners.push(speed.newListener([&](int&){
 setMovingSpeed(speed.get());
	}));
 }
 
 int Servo::getID(){
	return this->id;
 }
 
 
 int Servo::getPositionMinimum()
 {
	return this->positionMinimum;
 }
 
 int Servo::getPositionMaximum()
 {
	return this->positionMaximum;
 }
 
 int Servo::getTurnsCount()
 {
	return this->turnsCount;
 }
 
 
 std::shared_ptr<Connection> Servo::getConnection(){
	if(!connection.expired()){
 return connection.lock();
	}
	return nullptr;
 }
 
 void Servo::setID(int id)
 {
	this->id = id;
 }
 
 void Servo::setPositionMinimum(int positionMinimum)
 {
	this->positionMinimum = positionMinimum;
 }
 
 void Servo::setPositionMaximum(int positionMaximum){
	this->positionMaximum = positionMaximum;
 }
 
 void Servo::setTurnsCount(int turnsCount){
	this->turnsCount = turnsCount;
 }
 
 void Servo::setConnection(std::shared_ptr<Connection> connection){
	this->connection = connection;
 }
 
 bool Servo::ping()
 {
	auto c = getConnection();
	if(c){
 return c->ping(id);
	}
	return false;
 }
 
 bool Servo::reset(ResetOption option)
 {
	auto c = getConnection();
	if(c){
 return c->reset(id, option);
	}
	return false;
 }
 
 bool Servo::initialize()
 {
	auto c = getConnection();
	if(c){
 return c->clearPort();
	}
	return false;	
 }
 
 
 void Servo::stop()
 {
	auto c = getConnection();
	if(c){
 return c->closePort();
	}
 }
 
 bool Servo::move(int goalPosition, int movingSpeed){
	setMovingSpeed(movingSpeed);
	return setGoalPosition(goalPosition);
 }
 
 void Servo::moveWithAcceleration(int goalPosition, int movingSpeed, int accelerationSpeed)
 {
	
	//TODO: Check algorithm. Should start at current position
	int acceleration = accelerationSpeed;
	int position = accelerationSpeed;
	int movingspeed = 0;
	int i = 1;
	while (movingspeed < movingSpeed) {
 while (moving()) {
 }
 setMovingSpeed(accelerationSpeed * i);
 setGoalPosition(position * i);
 i++;
 movingspeed = acceleration * i;
	}
	setMovingSpeed(movingSpeed);
	setGoalPosition(goalPosition);
 }
 
 void Servo::readData(uint16_t address) {
	auto c = getConnection();
	if(c){
 
 if(address == SERVO_MODEL::GOAL_POSITION ||
 address == SERVO_MODEL::MOVING_SPEED ||
 address == SERVO_MODEL::TORQUE_LIMIT ||
 address == SERVO_MODEL::PUNCH ||
 address == SERVO_MODEL::PRESENT_POSITION ||
 address == SERVO_MODEL::PRESENT_SPEED ||
 address == SERVO_MODEL::PRESENT_LOAD ||
 address == SERVO_MODEL::MODEL_NUMBER ||
 address == SERVO_MODEL::CW_ANGLE_LIMIT ||
 address == SERVO_MODEL::CCW_ANGLE_LIMIT ||
 address == SERVO_MODEL::MAX_TORQUE){
 c->getPacketHandler()->read2ByteTxRx(c->getPortHandler().get(), id, address, &data2Byte, &error);
 }
 else
 {
 c->getPacketHandler()->read1ByteTxRx(c->getPortHandler().get(), id, address, &data1Byte, &error);
 }
 //		printResultError();
	}
 }
 void Servo::printResultError(std::string succMsg) {
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
 
 int Servo::writeData(int address, int dataChange) {
	auto c = getConnection();
	if(c){
 
 if(address == SERVO_MODEL::GOAL_POSITION ||
 address == SERVO_MODEL::MOVING_SPEED ||
 address == SERVO_MODEL::TORQUE_LIMIT ||
 address == SERVO_MODEL::PUNCH ||
 address == SERVO_MODEL::PRESENT_POSITION ||
 address == SERVO_MODEL::PRESENT_SPEED ||
 address == SERVO_MODEL::PRESENT_LOAD ||
 address == SERVO_MODEL::MODEL_NUMBER ||
 address == SERVO_MODEL::CW_ANGLE_LIMIT ||
 address == SERVO_MODEL::CCW_ANGLE_LIMIT ||
 address == SERVO_MODEL::MAX_TORQUE){
 //			std::cout << "Write address: " << address << "  data: " << dataChange << std::endl; 
 return c->getPacketHandler()->write2ByteTxRx(c->getPortHandler().get(), id, address, (uint16_t)dataChange, &error);
 }
 else
 {
 return c->getPacketHandler()->write1ByteTxRx(c->getPortHandler().get(), id, address, (uint8_t)dataChange, &error);
 }
 printResultError(); 
	}
 }
 int Servo::modelNumber()
 {
	this->readData((uint16_t)SERVO_MODEL::MODEL_NUMBER);
	return data1Byte;
 }
 int Servo::firmwareVersion()
 {
	this->readData((uint16_t)SERVO_MODEL::FIRMWARE_VERSION);
	return data1Byte;
 }
 
 int Servo::baudRate()
 {
	this->readData((uint16_t)SERVO_MODEL::BAUD_RATE);
	return data1Byte;
 }
 
 int Servo::returnDelay()
 {
	this->readData((uint16_t)SERVO_MODEL::RETURN_DELAY_TIME);
	return data1Byte;
 }
 
 int Servo::CWAngleLimit()
 {
	this->readData((uint16_t)SERVO_MODEL::CW_ANGLE_LIMIT);
	return data1Byte;
 }
 
 int Servo::CCWAngleLimit()
 {
	this->readData((uint16_t)SERVO_MODEL::CCW_ANGLE_LIMIT);
	return data2Byte;
 }
 
 int Servo::limitTemperature()
 {
	this->readData((uint16_t)SERVO_MODEL::TEMPERATURE_LIMIT);
	return data1Byte;
 }
 
 int Servo::lowestLimitVoltage()
 {
	this->readData((uint16_t)SERVO_MODEL::MIN_VOLTAGE_LIMIT);
	return data1Byte;
 }
 
 int Servo::highestLimitVoltage()
 {
	this->readData((uint16_t)SERVO_MODEL::MAX_VOLTAGE_LIMIT);
	return data1Byte;
 }
 
 
 int Servo::lowestByteOfMaxTorque()
 {
	this->readData((uint16_t)SERVO_MODEL::MAX_TORQUE);
	return data2Byte;
 }
 
 int Servo::statusReturnLevel()
 {
	this->readData((uint16_t)SERVO_MODEL::STATUS_RETURN_LEVEL);
	return data1Byte;
 }
 
 int Servo::getAlarmLed()
 {
	this->readData((uint16_t)SERVO_MODEL::LED);
	return data1Byte;
 }
 int Servo::getAlarmShutdown()
 {
	this->readData((uint16_t)SERVO_MODEL::SHUTDOWN);
	return data1Byte;
 }
 
 bool Servo::setId(uint8_t newId)
 {
	return writeData((uint16_t)SERVO_MODEL::ID, newId);
	this->id = newId;
 }
 
 bool Servo::setReturnDelayTime(int delay)
 {
	return writeData((uint16_t)SERVO_MODEL::RETURN_DELAY_TIME, delay);
 }
 
 bool Servo::setCWAngleLimit(int limit)
 {
	return writeData((uint16_t)SERVO_MODEL::CW_ANGLE_LIMIT, limit);
 }
 
 bool Servo::setCCWAngleLimit(int limit)
 
 {
	return writeData((uint16_t)SERVO_MODEL::CCW_ANGLE_LIMIT, limit);
 }
 
 bool Servo::setLimitTemperature(unsigned char limitTemp)
 {
	return writeData((uint16_t)SERVO_MODEL::TEMPERATURE_LIMIT, limitTemp);
 }
 
 bool Servo::setLowestLimitVoltage(int limitvoltage)
 {
	return writeData((uint16_t)SERVO_MODEL::MIN_VOLTAGE_LIMIT, limitvoltage);
 }
 
 bool Servo::setHighestLimitVoltage(int limitvoltage)
 {
	return writeData((uint16_t)SERVO_MODEL::MAX_VOLTAGE_LIMIT, limitvoltage);
 }
 
 bool Servo::setLowestByteOfMaxTorque(int maxTorque)
 {
	return writeData((uint16_t)SERVO_MODEL::MAX_TORQUE, maxTorque);
 }
 
 bool Servo::setStatusReturnLevel(int level)
 {
	return writeData((uint16_t)SERVO_MODEL::STATUS_RETURN_LEVEL, level);
 }
 bool Servo::setAlarmLed(bool alarmedLed)
 {
	return writeData((uint16_t)SERVO_MODEL::LED, alarmedLed);
 }
 
 bool Servo::setAlarmShutdown(bool shutdonw)
 {
	return writeData((uint16_t)SERVO_MODEL::SHUTDOWN, shutdonw);
 }
 
 // RAM
 bool Servo::torqueEnabled()
 {
	this->readData((uint16_t)SERVO_MODEL::TORQUE_ENABLE);
	return data1Byte;
 }
 
 bool Servo::ledState()
 {
	this->readData((uint16_t)SERVO_MODEL::LED);
	return data1Byte;
 }
 
 //int	Servo::CWComplianceMargin()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::CW_COMPLIANCE_MARGIN);
 //	return data1Byte;
 //}
 //
 //int	Servo::CCWComplianceMargin()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::CCW_COMPLIANCE_MARGIN);
 //	return data1Byte;
 //}
 //
 //int	Servo::CWComplianceSlope()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::CW_COMPLIANCE_SLOPE);
 //	return data1Byte;
 //}
 //
 //int	Servo::CCWComplianceSlope()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::CCW_COMPLIANCE_SLOPE);
 //	return data1Byte;
 //}
 
 int Servo::goalPosition()
 {
	this->readData((uint16_t)SERVO_MODEL::GOAL_POSITION);
	return data2Byte;
 }
 
 int Servo::movingSpeed()
 {
	this->readData((uint16_t)SERVO_MODEL::MOVING_SPEED);
	return data1Byte;
 }
 
 int Servo::torqueLimit()
 {
	this->readData((uint16_t)SERVO_MODEL::TORQUE_LIMIT);
	return data2Byte;
 }
 
 int Servo::presentPosition()
 {
	this->readData((uint16_t)SERVO_MODEL::PRESENT_POSITION);
	return data2Byte;
 }
 
 int Servo::presentSpeed()
 {
	this->readData((uint16_t)SERVO_MODEL::PRESENT_SPEED);
	return data1Byte;
 }
 
 int Servo::presentLoad()
 {
	this->readData((uint16_t)SERVO_MODEL::PRESENT_LOAD);
	return data1Byte;
 }
 
 int	Servo::presentVoltage()
 {
	this->readData((uint16_t)SERVO_MODEL::PRESENT_VOLTAGE);
	return data1Byte;
 }
 
 int	Servo::presentTemperature()
 {
	this->readData((uint16_t)SERVO_MODEL::PRESENT_TEMPERATURE);
	return data1Byte;
 }
 
 //bool Servo::instructionRegistered()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::REDG);
 //	return data1Byte;
 //}
 
 bool Servo::moving()
 {
	this->readData((uint16_t)SERVO_MODEL::MOVING);
	return data1Byte;
 }
 
 //bool Servo::EEPROMLocked()
 //{
 //	this->readData((uint16_t)SERVO_MODEL::LOCKEEPROM);
 //	return data1Byte;
 //}
 
 int	Servo::punch()
 {
	this->readData((uint16_t)SERVO_MODEL::PUNCH);
	return data1Byte;
 }
 
 bool Servo::enableTorque(bool torque)
 {
	return writeData((uint16_t)SERVO_MODEL::TORQUE_ENABLE, (torque?1:0));
 }
 
 bool Servo::setLed(int led)
 {
	return writeData((uint16_t)SERVO_MODEL::LED, led);
 }
 
 //bool Servo::setCWComplianceMargin(int CWComplianceMargin)
 //{
 //	return writeData((uint16_t)SERVO_MODEL::CW_COMPLIANCE_MARGIN, CWComplianceMargin);
 //}
 //
 //bool Servo::setCCWComplianceMargin(int CCWComplianceMargin)
 //{
 //	return writeData((uint16_t)SERVO_MODEL::CCW_COMPLIANCE_MARGIN, CCWComplianceMargin);
 //}
 //
 //bool Servo::setCWComplianceSlope(int CWComplianceSlope)
 //{
 //	return writeData((uint16_t)SERVO_MODEL::CW_COMPLIANCE_SLOPE, CWComplianceSlope);
 //}
 //
 //bool Servo::setCCWComplianceSlope(int CCWComplianceSlope)
 //{
 //	return writeData((uint16_t)SERVO_MODEL::CCW_COMPLIANCE_SLOPE, CCWComplianceSlope);
 //}
 
 bool Servo::setGoalPosition(int goal_postion)
 {
 //	goal_postion = std::min(std::max(goal_postion, positionMinimum), positionMaximum);
	return writeData((uint16_t)SERVO_MODEL::GOAL_POSITION, goal_postion);
	
 }
 
 bool Servo::setMovingSpeed(int movingSpeed)
 {
	return writeData((uint16_t)SERVO_MODEL::MOVING_SPEED, movingSpeed);
 }
 
 bool Servo::setTorqueLimit(int torqueLimit)
 {
	return writeData((uint16_t)SERVO_MODEL::TORQUE_LIMIT, torqueLimit);
 }
 
 //bool Servo::lockEEPROM()
 //{
 //	return writeData((uint16_t)SERVO_MODEL::LOCKEEPROM, 1);
 //}
 //
 //bool Servo::unlockEEPROM()
 //{
 //	return writeData((uint16_t)SERVO_MODEL::LOCKEEPROM, 0);
 //}
 
 int	Servo::setPunch(int punch)
 {
	return writeData((uint16_t)SERVO_MODEL::PUNCH, punch);
 }
 
 std::string Servo::getFullReportString(){
	std::stringstream ss;
	ss << "Model Number: " << modelNumber() << std::endl; // int 
	ss << "Firmware Version: " << firmwareVersion() << std::endl; // int 
	ss << "Baud Rate: " << baudRate() << std::endl; // int 
	ss << "Return Delay: " << returnDelay() << std::endl; // int 
	ss << "CW Angle Limit: " << CWAngleLimit() << std::endl; // int 
	ss << "CCW Angle Limit: " << CCWAngleLimit() << std::endl; // int 
	ss << "Limit Temperature: " << limitTemperature() << std::endl; // int 
	ss << "Lowest Limit Voltage: " << lowestLimitVoltage() << std::endl; // int 
	ss << "Highest Limit Voltage: " << highestLimitVoltage() << std::endl; // int 
	ss << "Lowest Byte Of Max Torque: " << lowestByteOfMaxTorque() << std::endl; // int 
	ss << "Status Return Level: " << statusReturnLevel() << std::endl; // int 
	ss << "Get Alarm Led: " << getAlarmLed() << std::endl; // int 
	ss << "Get Alarm Shutdown: " << getAlarmShutdown() << std::endl; // int 
	ss << "Torque Enabled: " << (torqueEnabled()?"YES":"NO") << std::endl; // bool 
	ss << "Led State: " << (ledState()?"YES":"NO") << std::endl; // bool 
	ss << "Goal Position: " << goalPosition() << std::endl; // int 
	ss << "Moving Speed: " << movingSpeed() << std::endl; // int 
	ss << "Torque Limit: " << torqueLimit() << std::endl; // int 
	ss << "Present Position: " << presentPosition() << std::endl; // int 
	ss << "Present Speed: " << presentSpeed() << std::endl; // int 
	ss << "Present Load: " << presentLoad() << std::endl; // int 
	ss << "Present Voltage: " << presentVoltage() << std::endl; // int	
	ss << "Present Temperature: " << presentTemperature() << std::endl; // int	
	ss << "Moving: " << (moving()?"YES":"NO") << std::endl; // bool 
	ss << "Punch: " << punch() << std::endl; // int	
	return ss.str();
 }
 
 
 
 void Servo::updateCurrentSpeed(){
	currentSpeed = presentSpeed();
 }
 void Servo::updateCurrentPosition(){
	currentPos = presentPosition();
 }

*/
	
	template class ServoGui<AX12>;
	template class ServoGui<XL320>;
}
