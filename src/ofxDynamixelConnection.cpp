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




