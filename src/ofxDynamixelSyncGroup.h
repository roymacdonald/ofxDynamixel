//
//  ofxDynamixelSyncGroup.h
//  test_autoDistribucion
//
//  Created by Roy Macdonald on 2/27/19.
//
//

#pragma once

#include "ofxDynamixelServo.h"
#include "ofxDynamixelServosModels.h"
namespace ofxDynamixel {
class SyncGroup{
public:
	
	virtual void setup(std::string param, std::shared_ptr<Connection> connection);
	
	std::shared_ptr<Connection> getConnection();
	void setConnection(std::shared_ptr<Connection> connection);

	
	void addServoToSync(std::shared_ptr<Servo<XL430> > servo);
	
	const std::vector<std::shared_ptr<Servo<XL430> >> & getSyncedServos();

	void sync();
	
protected:
	std::shared_ptr<dynamixel::GroupSyncRead> groupSync;
	std::vector<std::shared_ptr<Servo<XL430> >>synced;
	uint16_t paramId,  paramLength;
	std::string paramName;
private:
	std::weak_ptr<Connection> connection;
};	
}
