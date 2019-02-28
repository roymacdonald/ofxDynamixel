#include "ofxDynamixelConnection.h"

#include "port_handler.h"
#if defined(__linux__)
#include "port_handler_linux.h"
#define PORT_HANDLER_TYPE PortHandlerLinux
#elif defined(__APPLE__)
#include "port_handler_mac.h"
#define PORT_HANDLER_TYPE PortHandlerMac
#elif defined(_WIN32) || defined(_WIN64)
#include "port_handler_windows.h"
#define PORT_HANDLER_TYPE PortHandlerWindows
#endif
#include "protocol1_packet_handler.h"
#include "protocol2_packet_handler.h"

#include "ofLog.h"

using namespace dynamixel;

using namespace ofxDynamixel;
Connection::Connection(const std::string& portName, int protocolVersion, int baudrate){
	baudrate = baudrate;
	init(portName, protocolVersion);
}

Connection::Connection(){}
bool Connection::open(){
	return getPortHandler()->openPort();
}


void Connection::init(const std::string& portName, int protocolVersion){
	if(currentPortName.empty() || currentProtocolVersion == -1 || currentProtocolVersion != protocolVersion || currentPortName != portName){
		currentPortName = portName;
		currentProtocolVersion = protocolVersion;
		getPortHandler();//will create if is null
		getPacketHandler();//will create if is null	
	}else{
		ofLogVerbose("ofxDynamixel::Connection::init", "failed to init");
	}
}

bool Connection::connect(const std::string& portName, int protocolVersion, int baud){
	baudrate = baud;
	init(portName, protocolVersion);
	return open();
}

std::shared_ptr<PortHandler>  Connection::getPortHandler(){
	if(!portHandler){
		portHandler = std::make_shared<PORT_HANDLER_TYPE>(currentPortName.c_str());	
	}
	return portHandler;
}

std::shared_ptr<PacketHandler> Connection::getPacketHandler(){
	if(!packetHandler){
		if (currentProtocolVersion == 1){
			packetHandler = std::make_shared<Protocol1PacketHandler>();
		}else{//(protocolVersion == 2){
			packetHandler = std::make_shared<Protocol2PacketHandler>();
		}
	}
	return packetHandler;
}

bool Connection::setBaudRate(int baudrate){
	return getPortHandler()->setBaudRate(baudrate);
}
int Connection::getBaudRate(){
	return  getPortHandler()->getBaudRate();
}

bool Connection::ping(int id){
	if(packetHandler && portHandler){
		uint8_t error = 0;
		error = packetHandler->ping(portHandler.get(), id, &error);
		if (error != 0) {
			return false;
		}
		return true;
	}
	return false;
}
bool Connection::reboot(int id){
	if(packetHandler && portHandler){
		uint8_t error = 0;
		error = packetHandler->reboot(portHandler.get(), id, &error);
		if (error != 0) {
			return false;
		}
		return true;
	}
	return false;
}
bool Connection::reset(int id, ResetOption option){	
	if(packetHandler && portHandler){
		uint8_t error = 0;
		error = packetHandler->factoryReset(portHandler.get(), id, option, &error);
		if (error != 0) {
			return false;
		}
		return true;
	}
	return false;
}
bool Connection::clearPort(){
	if(portHandler){		
		portHandler->clearPort();
		return true;
	}
	return false;
}
bool Connection::closePort(){
	if(portHandler){		
		portHandler->closePort();
		return true;
	}
	return false;
}


std::shared_ptr<GroupBulkRead> Connection::getBulkReader(){
	if(packetHandler){ 
		if(portHandler && !groupBulkRead){
			groupBulkRead = std::make_shared<GroupBulkRead>(portHandler.get(), packetHandler.get());
		}
	}
	return groupBulkRead;
}
std::shared_ptr<GroupBulkWrite> Connection::getBulkWriter(){
	if(!groupBulkWrite){
		if(packetHandler && portHandler){
			groupBulkWrite = std::make_shared<GroupBulkWrite>(portHandler.get(), packetHandler.get());
		}
	}
	return groupBulkWrite;
}


///--------------------------------------------------------BULK READING
void Connection::clearBulkRead(){
	auto r = getBulkReader();
	if(!r)return false;
	r->clearParam();
	bulkReadIDs.clear();
}
bool Connection::addBulkReadParam(uint8_t id, uint16_t address, uint16_t data_length){
	auto r = getBulkReader();
	if(!r)return false;
	if (!r->addParam(id, address, data_length)){
		fprintf(stderr, "[ID:%03d] grouBulkRead addparam failed\n", id);
		return false;
	}
	bulkReadIDs.push_back(id);
	return true;
}
bool Connection::isBulkReadAvailable(uint8_t id, uint16_t address, uint16_t data_length){
	auto r = getBulkReader();
	if(!r)return false;
	if (!r->isAvailable(id, address, data_length)){
		fprintf(stderr, "[ID:%03d] groupBulkRead getdata failed\n", id);
		return false;
	}
	return false;
}

//template<typename T>
bool Connection::getBulkReadData(uint8_t id, uint16_t address, uint16_t data_length, uint16_t& data){
	if(isBulkReadAvailable(id, address, data_length)){
		data = getBulkReader()->getData(id, address, data_length);
		return true;
	}
	return false;
}
bool Connection::bulkReadRequest(){
	auto r = getBulkReader();
	if(!r)return false;
	if (r->txRxPacket() == COMM_SUCCESS){
		return true;
	}else{
		uint8_t dxl_error = 0;
		for(auto& id: bulkReadIDs){
			if (r->getError(id, &dxl_error)){
				printf("[ID:%03d] %s\n", id, packetHandler->getRxPacketError(dxl_error));
			}
		}
	}
	return false;
}

///--------------------------------------------------------BULK READING end

std::string Connection::getTxRxResult     (int result){
	if(packetHandler){
		return packetHandler->getTxRxResult(result);
	}
	return "packetHandler is null";
}
std::string Connection::getRxPacketError  (uint8_t error){
	if(packetHandler){
		return packetHandler->getRxPacketError(error);
	}
	return "packetHandler is null";
}



