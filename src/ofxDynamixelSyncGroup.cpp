//
//  ofxDynamixelSyncGroup.cpp
//  test_autoDistribucion
//
//  Created by Roy Macdonald on 2/27/19.
//
//

#include "ofxDynamixelSyncGroup.h"

namespace ofxDynamixel {
	
	void SyncGroup::setup( std::string param, std::shared_ptr<Connection> connection){
		setConnection(connection);
		
		paramName = param;
		
		
		//		dynamixel::GroupSyncRead groupSyncRead(portHandler, packetHandler, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
		
	}
	
	void SyncGroup::addServoToSync(std::shared_ptr<Servo<XL430> > servo){
		if(servo){
			if(!groupSync){
				auto c = getConnection();
				if(c){
					if(servo->model.table.count(paramName)){
						paramId = servo->model.table[paramName]->address;
						paramLength = servo->model.table[paramName]->getLength();
						groupSync = std::make_shared<dynamixel::GroupSyncRead>(c->getPortHandler().get(), c->getPacketHandler().get(), paramId, paramLength);
					}
				}
				
				//			ofLogError("ofxDynamixel::SyncGroup::addServoToSync", "sync group not setup. call setup method on before calling this one");
				//			return;
			}
			
			for(auto& s: synced){
				if(s.get() == servo.get()){
					ofLogWarning("ofxDynamixel::SyncGroup::addServoToSync", "servo already present in group. not adding it");
					return;
				}
			}
			
			if (!groupSync->addParam(servo->getId())){
				ofLogWarning("ofxDynamixel::SyncGroup::addServoToSync", "failed adding servo " + ofToString(servo->getId())+ " to sync group.");
				return;
			}
			
			synced.push_back(servo);
		}
	}
	
	const std::vector<std::shared_ptr<Servo<XL430> >> & SyncGroup::getSyncedServos(){
		return synced;
	}
	
	void SyncGroup::sync(){
		if(!groupSync){
			ofLogError("ofxDynamixel::SyncGroup::sync", "sync group not setup. call setup method on before calling this one");
			return;
		}
		auto dxl_comm_result = groupSync->txRxPacket();
		auto c = getConnection();
		
		if(c){
			if (dxl_comm_result != COMM_SUCCESS){
				ofLogWarning("ofxDynamixel::SyncGroup::sync", "sync failed. " + c->getTxRxResult(dxl_comm_result));
				return;
			}
			uint8_t dxl_error;
			for(auto& s: synced){
				if (groupSync->getError(s->getId(), &dxl_error)){
					ofLogWarning("ofxDynamixel::SyncGroup::sync", "servo id: " + ofToString(s->getId()) + " sync error. " + c->getRxPacketError(dxl_error));
				}
			}
			
			for(auto& s: synced){
				// Check if groupsyncread data of Dynamixel is available
				if(!groupSync->isAvailable(s->getId(), paramId, paramLength)){
					ofLogWarning("ofxDynamixel::SyncGroup::sync", "servo id: " + ofToString(s->getId()) + "getdata failed");
					return ;
				}
			}		
			for(auto& servo: synced){
				// Get Dynamixel#1 present position value
				if(!servo->model.table.count(paramName)){
					ofLogError("ofxDynamixel::SyncGroup::sync", "servo id: " + ofToString(servo->getId()) + " does not have parameter " + paramName);
					continue;
				}
				//			baseDxlParameter * s = servo->model.table[paramName]; 
				servo->model.table[paramName]->setReadOnlyValue( groupSync->getData(servo->getId(), paramId, paramLength)); 
			}
		}
	}
	
	
	std::shared_ptr<Connection> SyncGroup::getConnection(){
		if(!connection.expired()){
			return connection.lock();
		}
		return nullptr;
	}
	void SyncGroup::setConnection(std::shared_ptr<Connection> connection){
		this->connection = connection;
	}
}
