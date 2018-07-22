
#pragma once
#include <memory>
#include <string>
#include "ofxDynamixelConnection.h"

#include "ofParameter.h"

namespace ofxDynamixel {
class Servo{
public:

	
	Servo(){}
	
	virtual ~Servo(){}
	Servo(Servo&);
	Servo& operator=(Servo&);
	
	
	
	void setup(int id,  std::shared_ptr<Connection> connection);
	int getID();


	int getPositionMinimum();


	int getPositionMaximum();

	int getTurnsCount();

	
	std::shared_ptr<Connection> getConnection();


	void setID(int id);

	void setPositionMinimum(int positionMin);


	void setPositionMaximum(int positionMax);


	void setTurnsCount(int turnsCount);


	void setConnection(std::shared_ptr<Connection> connection);


	bool ping();


	bool reset(ResetOption option = RESET_ALL_BUT_ID_AND_BAUD);


	bool initialize();



	void stop();
	bool reboot();
	
	bool move(int goalPosition, int movingSpeed = -1);
	
	void moveWithAcceleration(int goalPosition, int movingSpeed, int accelerationSpeed);
	
	
	void readData(uint16_t address);
	int writeData(int address, int dataChange);
	int modelNumber();
	int firmwareVersion();
	int baudRate();
	int returnDelay();
	int CWAngleLimit();
	int CCWAngleLimit();
	int limitTemperature();
	int lowestLimitVoltage();
	int highestLimitVoltage();
	int lowestByteOfMaxTorque();
	int statusReturnLevel();
	int getAlarmLed();
	int getAlarmShutdown();
	bool setId(uint8_t newId);
	bool setReturnDelayTime(int delay);
	bool setCWAngleLimit(int limit);
	bool setCCWAngleLimit(int limit);
	bool setLimitTemperature(unsigned char limitTemp);
	bool setLowestLimitVoltage(int limitVoltage);
	bool setHighestLimitVoltage(int limitVoltage);
	bool setLowestByteOfMaxTorque(int maxTorque);
	bool setStatusReturnLevel(int level);
	bool setAlarmLed(bool led);
	bool setAlarmShutdown(bool shutdonw);
	
	// RAM
	bool torqueEnabled();
	bool ledState();
//	int	CWComplianceMargin();
//	int	CCWComplianceMargin();
//	int	CWComplianceSlope();
//	int	CCWComplianceSlope();
	int goalPosition();
	int movingSpeed();
	int torqueLimit();
	int presentPosition();
	int presentSpeed();
	int presentLoad();
	int	presentVoltage();
	int	presentTemperature();
	bool instructionRegistered();
	bool moving();
	bool EEPROMLocked();
	int	punch();
	bool enableTorque(bool torque);
	bool setLed(int led);
//	bool setCWComplianceMargin(int CWComplianceMargin);
//	bool setCCWComplianceMargin(int CCWComplianceMargin);
//	bool setCWComplianceSlope(int CWComplianceSlope);
//	bool setCCWComplianceSlope(int CCWComplianceSlope);
	bool setGoalPosition(int goalpostion);
	bool setMovingSpeed(int movingSpeed);
	bool setTorqueLimit(int torqueLimit);
//	bool lockEEPROM();
//	bool unlockEEPROM();
	int	setPunch(int puch);
	
	ofParameterGroup parameters;
	
private:
	
	int comm_result = COMM_TX_FAIL;
	uint8_t error;
	
	uint8_t data1Byte;
	
	uint16_t data2Byte;
	
	ofParameter<int> id, position, speed;
	
	ofEventListeners listeners;
	
	void setListeners();
	
	int positionMinimum;
	int positionMaximum;
	
	int turnsCount;
	
	std::weak_ptr<Connection> connection;
	
	void printResultError(std::string succMsg = "");

};

}
