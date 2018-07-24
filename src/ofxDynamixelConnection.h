/*!
 * \file	ofConnexion.h.
 * \brief	Declares the of connexion class.
 */

#pragma once
#include "dynamixel_sdk.h"
#include <string>
#include <memory>
#include "ofxDynamixelConstants.h"
 /*!
  * \class	ofConnexion
  *
  * \brief	The ofConnexion class.
  *
  * \author	Abdessalam Ghiouar
  * \version 0.1
  * \date	April 25, 2017
  */

namespace ofxDynamixel {
	using namespace dynamixel;
class Connection{
public:

	/*!
	 * \fn	ofConnexion::ofConnexion(const char * portName, float protocolVersion, int baudrate);
	 *
	 * \brief	Constructor of the ofConnexion class, Creates instance of ofConnexion.
	 *
	 * \param	portName	   	COM port device name.
	 * \param	protocolVersion	Version of the communication protocol used in Dynamixel.
	 * \param	baudrate	   	Baud Rate of Dynamixel.
	 */

	Connection(const std::string& portName, int protocolVersion = 2, int baudrate = 57600);

	/*!
	 * \fn	ofConnexion::ofConnexion();
	 *
	 * \brief	Constructor of the ofConnexion class, Creates instance of {@link ofConnexion}.
	 */

	Connection();



	/*!
	 * \fn	bool ofConnexion::open();
	 *
	 * \brief	Open a connection with Dynamixel.
	 *
	 * \return	True if the connection is established, false otherwise.
	 */

	bool open();

	/*!
	 * \fn	void ofConnexion::connect(const char * portName, float protocolVersion, int baudrate);
	 *
	 * \brief	Create a new connection with Dynamixel.
	 *
	 * \param	portName	   	COM port device name.
	 * \param	protocolVersion	Version of the communication protocol used in Dynamixel.
	 * \param	baudrate	   	Baud Rate of Dynamixel.
	 */

	bool connect(const std::string& portName, int protocolVersion, int baudrate);

	/*!
	 * \fn	dynamixel::PortHandler * ofConnexion::getPortHandler();
	 *
	 * \brief	Get the port handler.
	 *
	 * \return	The port handler.
	 */

	std::shared_ptr<PortHandler> getPortHandler();

	/*!
	 * \fn	dynamixel::PacketHandler * ofConnexion::getPacketHandler();
	 *
	 * \brief	Get the packet handler.
	 *
	 * \return	The packet handler.
	 */

	std::shared_ptr<PacketHandler> getPacketHandler();

	/*!
	 * \fn	int ofConnexion::getBaudRate();
	 *
	 * \brief	Get the  baud rate.
	 *
	 * \return	the baud rate.
	 */

	int getBaudRate();

	/*!
	 * \fn	bool ofConnexion::setBaudRate(int baudrate);
	 *
	 * \brief	Set the  baud rate.
	 *
	 * \param	baudrate	the  baud rate.
	 *
	 * \return	true if success set of the new baud rate.
	 */

	bool setBaudRate(int baudrate);
	
	/*!
	 * \fn	bool ping(int id);
	 *
	 * \brief	Ping the dynamixel.
	 *
	 * \param	id	Dynamixel ID.
	 *
	 * \return	true if success ping, false if not.
	 */
	bool ping(int id);
	bool reset(int id, ResetOption option = RESET_ALL_BUT_ID_AND_BAUD);
	
	bool clearPort();
	
	bool closePort();
	
	std::shared_ptr<GroupBulkRead> getBulkReader();
	std::shared_ptr<GroupBulkWrite> getBulkWriter();
	
	void clearBulkRead();
	bool addBulkReadParam(uint8_t id, uint16_t address, uint16_t data_length);
	bool isBulkReadAvailable(uint8_t id, uint16_t address, uint16_t data_length);
//	template<typename T>
	bool getBulkReadData(uint8_t id, uint16_t address, uint16_t data_length, uint16_t& data);
	bool bulkReadRequest();
	
	
private:
	/*! \brief	The baudrate */
	int baudrate;
	void init(const std::string& portName, int protocolVersion);
	std::string currentPortName;
	int currentProtocolVersion = - 1;
	std::shared_ptr<PortHandler> portHandler = nullptr;
	std::shared_ptr<PacketHandler> packetHandler = nullptr;
	std::shared_ptr<GroupBulkRead> groupBulkRead = nullptr;//(portHandler, packetHandler);
	std::shared_ptr<GroupBulkWrite> groupBulkWrite = nullptr;
	std::vector<uint8_t> bulkReadIDs;
};

}
