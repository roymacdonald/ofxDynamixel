#include "ofxDynamixel.h"


using namespace ofxDynamixel;


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
	parameters.add(speed.set("speed", 1000, 0, 2048));
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
		
		if(address == GOAL_POSITION ||
		   address == MOVING_SPEED ||
		   address == TORQUE_LIMIT ||
		   address == PUNCH ||
		   address == PRESENT_POSITION ||
		   address == PRESENT_SPEED ||
		   address == PRESENT_LOAD ||
		   address == MODEL_NUMBER ||
		   address == CW_ANGLE_LIMIT ||
		   address == CCW_ANGLE_LIMIT ||
		   address == MAX_TORQUE){
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
		
		if(address == GOAL_POSITION ||
		   address == MOVING_SPEED ||
		   address == TORQUE_LIMIT ||
		   address == PUNCH ||
		   address == PRESENT_POSITION ||
		   address == PRESENT_SPEED ||
		   address == PRESENT_LOAD ||
		   address == MODEL_NUMBER ||
		   address == CW_ANGLE_LIMIT ||
		   address == CCW_ANGLE_LIMIT ||
		   address == MAX_TORQUE){
			std::cout << "Write address: " << address << "  data: " << dataChange << std::endl; 
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
	this->readData((uint16_t)Register::MODEL_NUMBER);
	return data1Byte;
}
int Servo::firmwareVersion()
{
	this->readData((uint16_t)Register::FIRMWARE_VERSION);
	return data1Byte;
}

int Servo::baudRate()
{
	this->readData((uint16_t)Register::BAUD_RATE);
	return data1Byte;
}

int Servo::returnDelay()
{
	this->readData((uint16_t)Register::RETURN_DELAY_TIME);
	return data1Byte;
}

int Servo::CWAngleLimit()
{
	this->readData((uint16_t)Register::CW_ANGLE_LIMIT);
	return data1Byte;
}

int Servo::CCWAngleLimit()
{
	this->readData((uint16_t)Register::CCW_ANGLE_LIMIT);
	return data2Byte;
}

int Servo::limitTemperature()
{
	this->readData((uint16_t)Register::TEMPERATURE_LIMIT);
	return data1Byte;
}

int Servo::lowestLimitVoltage()
{
	this->readData((uint16_t)Register::MIN_VOLTAGE_LIMIT);
	return data1Byte;
}

int Servo::highestLimitVoltage()
{
	this->readData((uint16_t)Register::MAX_VOLTAGE_LIMIT);
	return data1Byte;
}


int Servo::lowestByteOfMaxTorque()
{
	this->readData((uint16_t)Register::MAX_TORQUE);
	return data2Byte;
}

int Servo::statusReturnLevel()
{
	this->readData((uint16_t)Register::STATUS_RETURN_LEVEL);
	return data1Byte;
}

int Servo::getAlarmLed()
{
	this->readData((uint16_t)Register::LED);
	return data1Byte;
}
int Servo::getAlarmShutdown()
{
	this->readData((uint16_t)Register::SHUTDOWN);
	return data1Byte;
}

bool Servo::setId(uint8_t newId)
{
	return writeData((uint16_t)Register::ID, newId);
	this->id = newId;
}

bool Servo::setReturnDelayTime(int delay)
{
	return writeData((uint16_t)Register::RETURN_DELAY_TIME, delay);
}

bool Servo::setCWAngleLimit(int limit)
{
	return writeData((uint16_t)Register::CW_ANGLE_LIMIT, limit);
}

bool Servo::setCCWAngleLimit(int limit)

{
	return writeData((uint16_t)Register::CCW_ANGLE_LIMIT, limit);
}

bool Servo::setLimitTemperature(unsigned char limitTemp)
{
	return writeData((uint16_t)Register::TEMPERATURE_LIMIT, limitTemp);
}

bool Servo::setLowestLimitVoltage(int limitvoltage)
{
	return writeData((uint16_t)Register::MIN_VOLTAGE_LIMIT, limitvoltage);
}

bool Servo::setHighestLimitVoltage(int limitvoltage)
{
	return writeData((uint16_t)Register::MAX_VOLTAGE_LIMIT, limitvoltage);
}

bool Servo::setLowestByteOfMaxTorque(int maxTorque)
{
	return writeData((uint16_t)Register::MAX_TORQUE, maxTorque);
}

bool Servo::setStatusReturnLevel(int level)
{
	return writeData((uint16_t)Register::STATUS_RETURN_LEVEL, level);
}
bool Servo::setAlarmLed(bool alarmedLed)
{
	return writeData((uint16_t)Register::LED, alarmedLed);
}

bool Servo::setAlarmShutdown(bool shutdonw)
{
	return writeData((uint16_t)Register::SHUTDOWN, shutdonw);
}

// RAM
bool Servo::torqueEnabled()
{
	this->readData((uint16_t)Register::TORQUE_ENABLE);
	return data1Byte;
}

bool Servo::ledState()
{
	this->readData((uint16_t)Register::LED);
	return data1Byte;
}

//int	Servo::CWComplianceMargin()
//{
//	this->readData((uint16_t)Register::CW_COMPLIANCE_MARGIN);
//	return data1Byte;
//}
//
//int	Servo::CCWComplianceMargin()
//{
//	this->readData((uint16_t)Register::CCW_COMPLIANCE_MARGIN);
//	return data1Byte;
//}
//
//int	Servo::CWComplianceSlope()
//{
//	this->readData((uint16_t)Register::CW_COMPLIANCE_SLOPE);
//	return data1Byte;
//}
//
//int	Servo::CCWComplianceSlope()
//{
//	this->readData((uint16_t)Register::CCW_COMPLIANCE_SLOPE);
//	return data1Byte;
//}

int Servo::goalPosition()
{
	this->readData((uint16_t)Register::GOAL_POSITION);
	return data2Byte;
}

int Servo::movingSpeed()
{
	this->readData((uint16_t)Register::MOVING_SPEED);
	return data1Byte;
}

int Servo::torqueLimit()
{
	this->readData((uint16_t)Register::TORQUE_LIMIT);
	return data2Byte;
}

int Servo::presentPosition()
{
	this->readData((uint16_t)Register::PRESENT_POSITION);
	return data2Byte;
}

int Servo::presentSpeed()
{
	this->readData((uint16_t)Register::PRESENT_SPEED);
	return data1Byte;
}

int Servo::presentLoad()
{
	this->readData((uint16_t)Register::PRESENT_LOAD);
	return data1Byte;
}

int	Servo::presentVoltage()
{
	this->readData((uint16_t)Register::PRESENT_VOLTAGE);
	return data1Byte;
}

int	Servo::presentTemperature()
{
	this->readData((uint16_t)Register::PRESENT_TEMPERATURE);
	return data1Byte;
}

//bool Servo::instructionRegistered()
//{
//	this->readData((uint16_t)Register::REDG);
//	return data1Byte;
//}

bool Servo::moving()
{
	this->readData((uint16_t)Register::MOVING);
	return data1Byte;
}

//bool Servo::EEPROMLocked()
//{
//	this->readData((uint16_t)Register::LOCKEEPROM);
//	return data1Byte;
//}

int	Servo::punch()
{
	this->readData((uint16_t)Register::PUNCH);
	return data1Byte;
}

bool Servo::enableTorque(bool torque)
{
	return writeData((uint16_t)Register::TORQUE_ENABLE, torque);
}

bool Servo::setLed(int led)
{
	return writeData((uint16_t)Register::LED, led);
}

//bool Servo::setCWComplianceMargin(int CWComplianceMargin)
//{
//	return writeData((uint16_t)Register::CW_COMPLIANCE_MARGIN, CWComplianceMargin);
//}
//
//bool Servo::setCCWComplianceMargin(int CCWComplianceMargin)
//{
//	return writeData((uint16_t)Register::CCW_COMPLIANCE_MARGIN, CCWComplianceMargin);
//}
//
//bool Servo::setCWComplianceSlope(int CWComplianceSlope)
//{
//	return writeData((uint16_t)Register::CW_COMPLIANCE_SLOPE, CWComplianceSlope);
//}
//
//bool Servo::setCCWComplianceSlope(int CCWComplianceSlope)
//{
//	return writeData((uint16_t)Register::CCW_COMPLIANCE_SLOPE, CCWComplianceSlope);
//}

bool Servo::setGoalPosition(int goal_postion)
{
//	goal_postion = std::min(std::max(goal_postion, positionMinimum), positionMaximum);
	return writeData((uint16_t)Register::GOAL_POSITION, goal_postion);
	
}

bool Servo::setMovingSpeed(int movingSpeed)
{
	return writeData((uint16_t)Register::MOVING_SPEED, movingSpeed);
}

bool Servo::setTorqueLimit(int torqueLimit)
{
	return writeData((uint16_t)Register::TORQUE_LIMIT, torqueLimit);
}

//bool Servo::lockEEPROM()
//{
//	return writeData((uint16_t)Register::LOCKEEPROM, 1);
//}
//
//bool Servo::unlockEEPROM()
//{
//	return writeData((uint16_t)Register::LOCKEEPROM, 0);
//}

int	Servo::setPunch(int punch)
{
	return writeData((uint16_t)Register::PUNCH, punch);
}



